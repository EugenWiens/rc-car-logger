import os.path

Import('env')


def getPathOfModuleDefines(env) -> str:
    projectBuildDir = env.get("PROJECT_BUILD_DIR")
    pioEnvironmen = env.get("PIOENV")

    return os.path.join(projectBuildDir, pioEnvironmen, 'include')


def exportIncludePath(env, outputFolder):
    env.Append(CPPPATH=[
        outputFolder
    ])

def generateDefineFile(env, outputFolder):
    libList = env.GetProjectOption("lib_deps")

    with open(os.path.join(outputFolder, 'ModulesDefines.hpp'), 'w') as file:
        for libName in libList:
            normalizeName =getNormalizeName(libName)
            file.write(f'#define {normalizeName}\n')


def getNormalizeName(name: str) -> str:
    normalizedString = name.upper()
    normalizedString = normalizedString.replace('-', '_')

    return normalizedString

outputFolder = getPathOfModuleDefines(env)
os.makedirs(outputFolder, exist_ok=True)
generateDefineFile(env, outputFolder)
exportIncludePath(env, outputFolder)
