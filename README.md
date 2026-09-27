# fhm-analytics

Tool that crunches data from *Franchise Hockey Manager* to filter the best players.

> *Note:* The project is a work-in-progress. I only own a copy of FHM 8 so I can't confirm it works on other versions.

## Build

```bash
rm -rf build;
mkdir build;
cd build;
cmake .. -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake";
cd ..;
cmake --build build --config Release
```

## TODO

1. Custom filter system
2. Sorting by categories
3. Handle goalies
4. Optimize parsing (for fun)

## Contributions

At this time, `fhm-analytics` is not accepting external contributions, but we welcome feedback and suggestions!
