#! /bin/env python3
import argparse
import os
import re
import shutil
import subprocess
import sys
import textwrap

from datetime import date, datetime
from pathlib import Path

DEBUG = 0


def log(fmt, *args):
    print(fmt.format(*args))


def debug(fmt, *args):
    if DEBUG > 0:
        log("-- "+fmt, *args)


def die(status, fmt, *args):
    log("ERROR: " + fmt, *args)
    sys.exit(status)


class Changes:
    def __init__(self, change_date: date, version: str):
        self.changes = []
        self.cdate = change_date
        self.version = version




def write_deb_log(changelog: Changes, args):

    header = f"libsilkit ({changelog.version}-1ubuntu1) stable; urgency=medium"

    changes = []

    class Change:

        def __init__(self):
            self.lines = []

        def pretty(self):
            text_block = ""
            for line in self.lines:
                text_block += line + "\n"
            return text_block.rstrip()

    def write_new_entry(changelog: Changes, header: str, filename: str):

        lines = []
        with open(filename, 'r') as f:
            lines = f.readlines()

        with open(filename.name + '.tmp', 'w') as f:
            f.write('\n' + header + '\n')
            for change in changelog.changes:
                change_p = '\n'.join(textwrap.wrap(change, width=76, subsequent_indent='    '))
                f.write('  * ' + change_p + '\n')

            for line in lines:
                f.write(line)

    for change in changelog.changes:
        text_block = textwrap.wrap(change, width=76)
        c = Change()
        c.lines.append(f"  * {text_block[0]}")
        for line in text_block[1:]:
            c.lines.append(f"    {line}")
        changes.append(c)

    # add footer
    c = Change()
    c.lines.append(
        f"\n -- {args.name} <{args.mail}> {changelog.cdate.strftime('%a, %d %b %Y')} {datetime.now().astimezone().strftime('%H:%M:%S %z')}")
    changes.append(c)
    print(f"{header}\n")

    for change in changes:
        print(f"{change.pretty()}")

    changelog_path = args.package_dir / 'debian/changelog'
    write_new_entry(changelog, header, changelog_path)

    try:
        shutil.copy2('changelog.tmp', changelog_path)
    except Exception as e:
        die(f"Unable to copy the debian changelog file: {e}", 64)


def write_rpm_log(changelog: Changes, args):

    header = f"* {changelog.cdate.strftime('%a %b %d %Y')} {args.name} <{args.mail}> - {changelog.version}"

    changes = []

    class Change:

        def __init__(self):
            self.lines = []

        def pretty(self):
            text_block = ""
            for line in self.lines:
                text_block += line + "\n"
            return text_block.rstrip()

    def write_new_entry(changelog: Changes, header: str, filename: str):

        lines = []
        with open(filename, 'r') as f:
            lines = f.readlines()

        with open(filename.name + '.tmp', 'w') as f:

            for line in lines:
                f.write(line)

                if '%changelog' in line:
                    print("Writing new changelog entry!")
                    f.write('\n' + header + '\n')
                    for change in changelog.changes:
                        change_p = '\n'.join(textwrap.wrap(change, width=76, subsequent_indent='  '))
                        f.write('- ' + change_p + '\n')

    for change in changelog.changes:
        text_block = textwrap.wrap(change, width=76)
        c = Change()
        c.lines.append(f"- {text_block[0]}")
        for line in text_block[1:]:
            c.lines.append(f"  {line}")
        changes.append(c)

#    print(f"{header}\n")

    complete_text = header + '\n'
    for change in changes:
        complete_text += change.pretty() + "\\\\n"

    print(complete_text)

    changelog_path = args.package_dir / 'rpm/libsilkit5.spec'
    write_new_entry(changelog, header, changelog_path)

    try:
        shutil.copy2('libsilkit5.spec.tmp', changelog_path)
    except Exception as e:
        die(f"Unable to copy the rpm spec file: {e}", 64)


def main():

    print("Hello from the chaparone!")
    subc_list = ["Added", "Fixed", "Changed"]

    isCI = os.getenv("CI")

    parser = argparse.ArgumentParser(prog="ChaparONE",
                                     description="Parse and create changelogs for SIL Kit releases")
    parser.add_argument('name', type=str)
    parser.add_argument('mail', type=str)
    parser.add_argument('package_dir', type=Path)
    args = parser.parse_args()

    version_found = True

    changelog = None
    with open("../../docs/changelog/versions/latest.md") as f:

        for line in f:
            # Check Version
            if line.startswith('# '):

                print(line)

                if changelog is not None:
                    log("Older version, stopping the processing")
                    break
                ver_reg = r"^#\s\[([0-9]+\.[0-9]+\.[0-9]+)\]\s+\-\s+([0-9]+\-[0-9]+\-[0-9]+|UNRELEASED)"
                reg = re.match(ver_reg, line)

                release_date = date.today() if reg.group(2) == 'UNRELEASED' else date.fromisoformat(reg.group(2))
                changelog = Changes(release_date, reg.group(1))

                if isCI is not None:
                    with open(os.environ['GITHUB_OUTPUT'], 'a') as f:
                        f.write(f"silkit_version={changelog.version}\n")
                log(f"Found version {changelog.version} from {release_date}")

            if line.startswith("* ") or line.startswith('- '):

                if changelog is None:
                    die("Malformed changelog, no changelog header found!")

                changelog.changes.append(line[2:].strip())
                #print(changelog.changes[-1])

    write_deb_log(changelog, args)
    write_rpm_log(changelog, args)


if __name__ == "__main__":

    main()
