if exist licensed-assets\ (
  echo "Packaging licensed assets..."
  mkdir release
  robocopy build/Debug release /E /XF "*CoffeeMakerUnitTests*"
  robocopy assets release/assets /E
  robocopy licensed-assets/images release/assets/images /E
  7z a -r ultra-cosmo-invaders-win.zip .\release\*
) else (
  echo "Licensed assets will NOT be packaged..."
  mkdir release
  robocopy build/Debug release /E /XF "*CoffeeMakerUnitTests*"
  robocopy assets release/assets /E
  7z a -r ultra-cosmo-invaders-win.zip .\release\*
)


