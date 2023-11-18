import subprocess
import sys
import os


def clone_repository(repo_url, location):
    # Ensure the target directory exists
    os.makedirs(location, exist_ok=True)
    subprocess.check_call(['git', 'clone', repo_url], cwd=location)


clone_repository('https://github.com/Camwashere/nativefiledialog.git', 'lib')
