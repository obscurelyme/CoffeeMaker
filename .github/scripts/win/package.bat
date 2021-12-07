mkdir release
robocopy build/Debug release /E /XF "*CoffeeMakerUnitTests*"
robocopy assets release/assets /E
7z a -r ultra-cosmo-invaders-win.zip .\release\*
