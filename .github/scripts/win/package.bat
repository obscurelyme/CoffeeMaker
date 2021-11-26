mkdir release
robocopy build/Debug release /E
7z a -r ultra-cosmo-invaders-win.zip .\release\*
