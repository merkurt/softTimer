#include "./unity/unity.h"
#include "../src/soft_tim.h"

void setUp(void){;}
void tearDown(void){;}

int testVal = 0;

void testVal_reset(void){
    testVal = 0;
}

void test_callback(void){
    testVal += 1;
}

void test_softTimer_init(void){
    struct softTimer st;
    softTimer_init(&st);
    TEST_ASSERT_EQUAL(0, st.tick_ms);
    TEST_ASSERT_EQUAL(0, st.counter);
    TEST_ASSERT_EQUAL(0, st.interval);
    TEST_ASSERT_EQUAL(NULL, st.callback);
}

void test_softTimer_setInterval(void){
    struct softTimer st;
    softTimer_init(&st);
    TEST_ASSERT_EQUAL(0, st.interval);
    softTimer_setInterval(&st, 1000);
    TEST_ASSERT_EQUAL(1000, st.interval);
}

void test_softTimer_tickMs(void){
    struct softTimer st;
    softTimer_init(&st);
    TEST_ASSERT_EQUAL(0, st.tick_ms);
    softTimer_setTickMs(&st, 1);
    TEST_ASSERT_EQUAL(1, st.tick_ms);
}

void test_softTimer_resetCounter(void){
    struct softTimer st;
    softTimer_init(&st);
    TEST_ASSERT_EQUAL(0, st.counter);
    st.counter = 50;
    TEST_ASSERT_EQUAL(50, st.counter);
    softTimer_resetCounter(&st);
    TEST_ASSERT_EQUAL(0, st.counter);
}

void test_softTimer_setCallback(void){
    struct softTimer st;
    softTimer_init(&st);
    softTimer_setCallback(&st, test_callback);
    TEST_ASSERT_EQUAL(test_callback, st.callback);
    TEST_ASSERT_NOT_EQUAL(NULL, test_callback);
    TEST_ASSERT_NOT_EQUAL(NULL, st.callback);
}

void test_softTimer_tickHandler_basic(void){
    testVal_reset();
    TEST_ASSERT_EQUAL(0, testVal);
    struct softTimer st;
    softTimer_init(&st);
    softTimer_setTickMs(&st, 1);
    softTimer_setInterval(&st, 2);
    softTimer_setCallback(&st, test_callback);
    softTimer_tickHandler(&st);
    TEST_ASSERT_EQUAL(1, st.counter);
    softTimer_tickHandler(&st);
    TEST_ASSERT_EQUAL(1, testVal);
    TEST_ASSERT_EQUAL(0, st.counter);
}

void test_softTimer_tickHandler_complex(void){
    testVal_reset();
    TEST_ASSERT_EQUAL(0, testVal);
    struct softTimer st;
    softTimer_init(&st);
    softTimer_setTickMs(&st, 3);
    softTimer_setInterval(&st, 100);
    softTimer_setCallback(&st, test_callback);
    for(uint32_t i = 0 ; i < 50 ; ++i){
        softTimer_tickHandler(&st);
    }
    TEST_ASSERT_EQUAL(48, st.counter);
    TEST_ASSERT_EQUAL(1, testVal);
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(test_softTimer_init);
    RUN_TEST(test_softTimer_setInterval);
    RUN_TEST(test_softTimer_tickMs);
    RUN_TEST(test_softTimer_resetCounter);
    RUN_TEST(test_softTimer_setCallback);
    RUN_TEST(test_softTimer_tickHandler_basic);
    RUN_TEST(test_softTimer_tickHandler_complex);
    return UNITY_END();
}