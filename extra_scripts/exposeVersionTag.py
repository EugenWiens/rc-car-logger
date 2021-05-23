import subprocess

Import('env')


process = subprocess.run(['git', 'describe', '--tags', '--always'], stdout=subprocess.PIPE, text=True)
versionTag = process.stdout.strip()

env.Append(CPPDEFINES=[
    ('VERSION_TAG', f'\\"{versionTag}\\"')
])

