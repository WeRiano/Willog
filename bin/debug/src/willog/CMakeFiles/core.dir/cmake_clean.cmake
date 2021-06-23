file(REMOVE_RECURSE
  "Core.lib"
  "Core.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/Core.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
