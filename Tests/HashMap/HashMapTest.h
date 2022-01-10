#pragma once

#include "BaseTestTemplate.h"
#include "HashMap.h"

#define MAP_INITIAL_CAPACITY 4

static void *mapSetup(const MunitParameter params[], void *userData) {
    HashMap map = getHashMapInstance(MAP_INITIAL_CAPACITY);
    assert_not_null(map);
    return map;
}

static MunitResult testMapPutElements(const MunitParameter params[], void *map) {
    (HashMap) map;
    assert_true(hashMapPut(map, "val1", (MapValueType) 21));
    assert_true(hashMapPut(map, "val1", (MapValueType) 22));
    assert_true(hashMapPut(map, "val2", (MapValueType) 23));
    assert_true(hashMapPut(map, "val3", (MapValueType) 24));
    assert_true(hashMapPut(map, "val4", (MapValueType) 25));
    assert_true(hashMapPut(map, "val5", (MapValueType) 26));
    assert_true(hashMapPut(map, "val6", (MapValueType) 27));
    assert_true(hashMapPut(map, "val7", (MapValueType) 28));

    assert_int(getHashMapSize(map), ==, 7);

    assert_int((int) hashMapGet(map, "val1"), ==, 22);
    assert_int((int) hashMapGet(map, "val2"), ==, 23);
    assert_int((int) hashMapGet(map, "val3"), ==, 24);
    assert_int((int) hashMapGet(map, "val4"), ==, 25);
    assert_int((int) hashMapGet(map, "val5"), ==, 26);
    assert_int((int) hashMapGet(map, "val6"), ==, 27);
    assert_int((int) hashMapGet(map, "val7"), ==, 28);

    hashMapPut(map, "val7", (MapValueType) 288);
    assert_int((int) hashMapGet(map, "val7"), ==, 288);

    assert_int(getHashMapSize(map), ==, 7);
    return MUNIT_OK;
}

static MunitResult testMapGetElements(const MunitParameter params[], void *map) {
    (HashMap) map;
    hashMapPut(map, "val1", (MapValueType) 22);
    hashMapPut(map, "val2", (MapValueType) 23);
    hashMapPut(map, "val3", (MapValueType) 24);

    assert_int((int) hashMapGet(map, "val2"), ==, 23);
    assert_int((int) hashMapGet(map, "error"), ==, 0);

    assert_int((int) hashMapGetOrDefault(map, "val3", (MapValueType) 0), ==, 24);
    assert_int((int) hashMapGetOrDefault(map, "val4", (MapValueType) 33), ==, 33);

    assert_false(isHashMapContainsKey(map, "err"));
    assert_true(isHashMapContainsKey(map, "val3"));

    return MUNIT_OK;
}

static MunitResult testMapRemoveElements(const MunitParameter params[], void *map) {
    (HashMap) map;
    hashMapPut(map, "val1", (MapValueType) 22);
    hashMapPut(map, "val2", (MapValueType) 23);
    hashMapPut(map, "val3", (MapValueType) 24);

    assert_int((int) hashMapRemove(map, "val2"), ==, 23);
    assert_int((int) hashMapRemove(map, "val3"), ==, 24);
    assert_int((int) hashMapRemove(map, "err"), ==, 0);

    assert_int(getHashMapSize(map), ==, 1);

    assert_true(isHashMapContainsKey(map, "val1"));
    assert_false(isHashMapContainsKey(map, "val2"));
    assert_false(isHashMapContainsKey(map, "val3"));

    hashMapPut(map, "val4", (MapValueType) (MapValueType) 25);
    assert_int(getHashMapSize(map), ==, 2);

    return MUNIT_OK;
}

static MunitResult testMapIterator(const MunitParameter params[], void *map) {
    (HashMap) map;
    hashMapPut(map, "val1", (MapValueType) 22);
    hashMapPut(map, "val2", (MapValueType) 23);
    hashMapPut(map, "val3", (MapValueType) 24);

    HashMapIterator iterator = getHashMapIterator(map);
    while (hashMapHasNext(&iterator)) {
        assert_true(isHashMapContainsKey(map, iterator.key));
        int value = (int) hashMapGet(map, iterator.key);
        assert_true(value == 22 || value == 23 || value == 24);
    }

    return MUNIT_OK;
}

static MunitResult testMapSize(const MunitParameter params[], void *map) {
    (HashMap) map;
    hashMapPut(map, "val1", (MapValueType) 22);
    assert_int(getHashMapSize(map), ==, 1);
    assert_false(isHashMapEmpty(map));
    assert_true(isHashMapNotEmpty(map));

    hashMapRemove(map, "val1");
    assert_int(getHashMapSize(map), ==, 0);
    assert_true(isHashMapEmpty(map));
    assert_false(isHashMapNotEmpty(map));

    return MUNIT_OK;
}

static MunitResult testMapAddAll(const MunitParameter params[], void *map) {
    HashMap fromMap = (HashMap) map;
    hashMapPut(map, "val1", (MapValueType) 22);
    hashMapPut(map, "val2", (MapValueType) 23);
    hashMapPut(map, "val3", (MapValueType) 24);

    HashMap toMap = getHashMapInstance(5);
    assert_not_null(toMap);
    hashMapPut(toMap, "val4", (MapValueType) 25);

    hashMapAddAll(fromMap, toMap);

    assert_true(isHashMapContainsKey(toMap, "val1"));
    assert_true(isHashMapContainsKey(toMap, "val2"));
    assert_true(isHashMapContainsKey(toMap, "val3"));
    assert_true(isHashMapContainsKey(toMap, "val4"));

    return MUNIT_OK;
}

static MunitResult testMapClear(const MunitParameter params[], void *map) {
    (HashMap) map;
    hashMapPut(map, "val1", (MapValueType) 22);
    hashMapPut(map, "val2", (MapValueType) 23);
    hashMapPut(map, "val3", (MapValueType) 24);
    assert_int(getHashMapSize(map), ==, 3);

    hashMapClear(map);
    assert_true(isHashMapEmpty(map));
    return MUNIT_OK;
}

static MunitResult testMapLoad(const MunitParameter params[], void *map) {
    (HashMap) map;
    for (int i = 0; i < 100000; i++) {
        hashMapPut(map, generateRandomString(10), (MapValueType) i);
    }
    assert_int(getHashMapSize(map), ==, 100000);

    HashMapIterator iterator = getHashMapIterator(map);
    while (hashMapHasNext(&iterator)) {
        hashMapRemove(map, iterator.key);
        free((char *) iterator.key);
    }
    assert_int(getHashMapSize(map), ==, 0);

    return MUNIT_OK;
}

static void mapTearDown(void *map) {
    hashMapDelete(map);
    map = NULL;
    munit_assert_ptr_null(map);
}


static MunitTest hashMapTests[] = {
        {
                .name =  "Test hashMapPut() - should correctly hold elements",
                .test = testMapPutElements,
                .setup = mapSetup,
                .tear_down = mapTearDown
        },
        {
                .name =  "Test hashMapGet() - should correctly return elements",
                .test = testMapGetElements,
                .setup = mapSetup,
                .tear_down = mapTearDown
        },
        {
                .name =  "Test hashMapRemove() - should correctly remove elements",
                .test = testMapRemoveElements,
                .setup = mapSetup,
                .tear_down = mapTearDown
        },
        {
                .name =  "Test getHashMapIterator() - should correctly iterate elements",
                .test = testMapIterator,
                .setup = mapSetup,
                .tear_down = mapTearDown
        },
        {
                .name =  "Test getHashMapSize() - should return correct map size",
                .test = testMapSize,
                .setup = mapSetup,
                .tear_down = mapTearDown
        },
        {
                .name =  "Test hashMapAddAll() - should correctly copy elements from map to map",
                .test = testMapAddAll,
                .setup = mapSetup,
                .tear_down = mapTearDown
        },
        {
                .name =  "Test testHashMapClear() - should clear map",
                .test = testMapClear,
                .setup = mapSetup,
                .tear_down = mapTearDown
        },
        {
                .name =  "Test hashMap Load - should collect and remove a lot of elements",
                .test = testMapLoad,
                .setup = mapSetup,
                .tear_down = mapTearDown
        },
        END_OF_TESTS
};

static const MunitSuite hashMapTestSuite = {
        .prefix = "HashMap: ",
        .tests = hashMapTests,
        .suites = NULL,
        .iterations = 1,
        .options = MUNIT_SUITE_OPTION_NONE
};