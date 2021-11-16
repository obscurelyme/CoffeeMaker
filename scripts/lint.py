import os
import subprocess
import time

directory = 'src'
sources = []
processes = []

def buildSources(dir):
  for sourceFile in os.listdir(dir):
    f = os.path.join(dir, sourceFile)
    if os.path.isfile(f):
      sources.append(f)
    else:
      buildSources(f)

buildSources('src')

if not os.path.exists('lint'):
  os.mkdir('lint')

for cpp in sources:
  filename = cpp.replace('/', '--').replace('.cpp', '')
  f = open('lint/%s-results.txt' % filename, 'w+')
  p = subprocess.Popen(['/usr/local/opt/llvm/bin/clang-tidy',
    '--config-file=.clang-tidy',
    cpp,
    '--',
    '-Iinclude',
    '-Ibuild/vcpkg_installed/x64-osx/include',
    '-std=c++20'], stdout=f, stderr=f)
  processes.append((p, f, False))

done = False

while not done:
  allNotDone = True

  for index, (proc, log, cmp) in enumerate(processes):
    if not proc.poll() is None:
      # we are done with this proc...
      if not cmp:
        log.close()
        processes[index] = (proc, log, True)
        print(">>> %s Successfully written" % log.name)
    else:
      allNotDone = False

  done = allNotDone
  time.sleep(0.5)
