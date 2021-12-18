# HashMap

[![tests](https://github.com/ximtech/HashMap/actions/workflows/cmake-ci.yml/badge.svg)](https://github.com/ximtech/HashMap/actions/workflows/cmake-ci.yml)

**STM32** lightweight implementation of HashMap.

## Key points to note:

- HashMap contains values based on the key
- HashMap cannot contain duplicate keys
- HashMap is an unordered collection. It does not guarantee any specific order of the elements
- HashMap keys should be unique. If you try to insert the duplicate key, it will replace the element of the corresponding key

### Features

- Specifically designed for embedded applications
- Constant time for data get and put
- Automatic size enlargement
- Easy to use and add to the project
- Performance optimized
- Map iterator implementation. Easy to loop through key and values
- No external dependencies
- Low memory consumption

### Trade-offs

- Mostly static Hash data type, can't be changed at runtime
- Only string as a key
- Not thread safe
- "Linear probing" algorithm. Can cause "data clustering" and long get operation for large amount of data

### Add as CPM project dependency
How to add CPM to the project, check the [link](https://github.com/cpm-cmake/CPM.cmake)
```cmake
CPMAddPackage(
        NAME HashMap
        GITHUB_REPOSITORY ximtech/HashMap
        GIT_TAG origin/main)

target_link_libraries(${PROJECT_NAME} HashMap)
```
```cmake
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
# For Clion STM32 plugin generated Cmake use 
target_link_libraries(${PROJECT_NAME}.elf HashMap)
```

### Usage

Example of usage:
```C
HashMap hashMap = getHashMapInstance(4);    // create first Map
hashMapPut(hashMap, "1", "one");
hashMapPut(hashMap, "2", "two");
hashMapPut(hashMap, "3", "three");  // add some values

printf("Map size: %d\n", getHashMapSize(hashMap));  // 3
printf("Single value: %s\n", hashMapGet(hashMap, "2")); // two

HashMapIterator iterator = getHashMapIterator(hashMap); // loop all keys and values
while (hashMapHasNext(&iterator)) {
    printf("Key: [%s], Value: [%s]\n", iterator.key, iterator.value);
}

hashMapRemove(hashMap, "1");    // element with key "1" will be removed from Map
printf("New size: %d\n", getHashMapSize(hashMap));  // 2

HashMap hashMap2 = getHashMapInstance(4);   // create second Map
hashMapPut(hashMap2, "4", "four");
hashMapPut(hashMap2, "5", "five");

hashMapAddAll(hashMap, hashMap2);   // merge two maps
iterator = getHashMapIterator(hashMap2);
while (hashMapHasNext(&iterator)) {
    printf("Key: [%s], Value: [%s]\n", iterator.key, iterator.value);
}
hashMapDelete(hashMap);
hashMapDelete(hashMap2);
```
