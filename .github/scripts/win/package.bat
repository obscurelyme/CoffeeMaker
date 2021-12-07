mkdir release
robocopy build/Debug release /E /XF "*CoffeeMakerUnitTests*"
7z a -r ultra-cosmo-invaders-win.zip .\release\*
