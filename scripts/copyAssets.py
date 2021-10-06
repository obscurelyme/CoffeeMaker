import os
import shutil
import platform

# class File:
#   def __init__(self, name, absPath, dirPath = []):
#     self.name = name
#     self.absPath = absPath
#     self.dirPath = dirPath

#   name = ""
#   absPath = ""
#   dirPath = []

# def copy(dirName, traversals = []):
#   for file in os.listdir(dirName):
#     filePath = os.path.join(dirName, file)
#     if (os.path.isdir(filePath)):
#       traversals.append(file)
#       print("Recursing %s" % filePath)
#       copy(filePath, traversals)
#     else:
#       copyTo = os.path.join(dest, "/".join(traversals), file)
#       print("Copying to...%s" % copyTo)
#       shutil.copy(filePath, os.path.join(dest, "/".join(traversals)))



baseDir = os.getcwd()
src = os.path.join(baseDir, "assets")
dest = ""
sys = platform.system()

if (sys == "Windows"):
  dest = os.path.join(baseDir, "build/Debug/assets")
else:
  dest = os.path.join(baseDir, "build/assets")

shutil.copytree(src, dest)
