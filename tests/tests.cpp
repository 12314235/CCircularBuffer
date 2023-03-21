#include "gtest/gtest.h"
#include "lib/CCircularBufferExt.h"
#include "lib/CCircularBuffer.h"
#include <vector>
#include <string>

TEST(CCircularBuffer, InitTestSimple){
    std::vector<int> init_vector = {1, 2, 3, 4, 5};
    std::initializer_list<int> init_list = {1, 2, 3, 4};
    size_t n = 5;
    int x = 5;

    CCircularBuffer<int> b_int_init_list = init_list;
    CCircularBuffer<int> b_int_construct_1 = CCircularBuffer<int>();
    CCircularBuffer<int> b_int_construct_2 = CCircularBuffer<int>(n, x);
    CCircularBuffer<int> b_int_construct_3 = CCircularBuffer<int>(init_vector.begin(), init_vector.end());
    CCircularBuffer<int> b_int_construct_4 = CCircularBuffer<int>(n);
    CCircularBuffer<int> b_copy = b_int_init_list;

    ASSERT_TRUE(std::equal(b_int_init_list.begin(), b_int_init_list.end(), init_list.begin(), init_list.end()));
    ASSERT_EQ(b_int_construct_1.size(), 0);
    ASSERT_EQ(b_int_construct_2.size(), n);
    for(auto i : b_int_construct_2){
        ASSERT_EQ(i, x);
    }
    ASSERT_TRUE(std::equal(b_int_construct_3.begin(), b_int_construct_3.end(), init_vector.begin(), init_vector.end()));
    ASSERT_TRUE(std::equal(b_copy.begin(), b_copy.end(), b_int_init_list.begin(), b_int_init_list.end()));
    ASSERT_EQ(b_int_construct_4.size(), 0);
    ASSERT_EQ(b_int_construct_4.capacity(), n);
}

TEST(CCircularBuffer, InitTestString){
    std::vector<std::string> init_vector = {"1", "2", "3", "4", "5"};
    std::initializer_list<std::string> init_list = {"1", "2", "3", "4"};
    size_t n = 5;
    std::string x = "5";

    CCircularBuffer<std::string> b_int_init_list = init_list;
    CCircularBuffer<std::string> b_int_construct_1 = CCircularBuffer<std::string>();
    CCircularBuffer<std::string> b_int_construct_2 = CCircularBuffer<std::string>(n, x);
    CCircularBuffer<std::string> b_int_construct_3 = CCircularBuffer<std::string>(init_vector.begin(), init_vector.end());
    CCircularBuffer<std::string> b_int_construct_4 = CCircularBuffer<std::string>(n);
    CCircularBuffer<std::string> b_copy = b_int_init_list;

    ASSERT_TRUE(std::equal(b_int_init_list.begin(), b_int_init_list.end(), init_list.begin(), init_list.end()));
    ASSERT_EQ(b_int_construct_1.size(), 0);
    ASSERT_EQ(b_int_construct_2.size(), n);
    for(auto i : b_int_construct_2){
        ASSERT_EQ(i, x);
    }
    ASSERT_TRUE(std::equal(b_int_construct_3.begin(), b_int_construct_3.end(), init_vector.begin(), init_vector.end()));
    ASSERT_TRUE(std::equal(b_copy.begin(), b_copy.end(), b_int_init_list.begin(), b_int_init_list.end()));
    ASSERT_EQ(b_int_construct_4.size(), 0);
    ASSERT_EQ(b_int_construct_4.capacity(), n);
}

TEST(CCircularBufferExt, InitTestSimple){
    std::vector<int> init_vector = {1, 2, 3, 4, 5};
    std::initializer_list<int> init_list = {1, 2, 3, 4};
    size_t n = 5;
    int x = 5;

    CCircularBufferExt<int> b_int_init_list = init_list;
    CCircularBufferExt<int> b_int_construct_1 = CCircularBufferExt<int>();
    CCircularBufferExt<int> b_int_construct_2 = CCircularBufferExt<int>(n, x);
    CCircularBufferExt<int> b_int_construct_3 = CCircularBufferExt<int>(init_vector.begin(), init_vector.end());
    CCircularBufferExt<int> b_int_construct_4 = CCircularBufferExt<int>(n);
    CCircularBufferExt<int> b_copy = b_int_init_list;

    ASSERT_TRUE(std::equal(b_int_init_list.begin(), b_int_init_list.end(), init_list.begin(), init_list.end()));
    ASSERT_EQ(b_int_construct_1.size(), 0);
    ASSERT_EQ(b_int_construct_2.size(), n);
    for(auto i : b_int_construct_2){
        ASSERT_EQ(i, x);
    }
    ASSERT_TRUE(std::equal(b_int_construct_3.begin(), b_int_construct_3.end(), init_vector.begin(), init_vector.end()));
    ASSERT_TRUE(std::equal(b_copy.begin(), b_copy.end(), b_int_init_list.begin(), b_int_init_list.end()));
    ASSERT_EQ(b_int_construct_4.size(), 0);
    ASSERT_EQ(b_int_construct_4.capacity(), n * 2);
}

TEST(CCircularBufferExt, InitTestString){
    std::vector<std::string> init_vector = {"1", "2", "3", "4", "5"};
    std::initializer_list<std::string> init_list = {"1", "2", "3", "4"};
    size_t n = 5;
    std::string x = "5";

    CCircularBufferExt<std::string> b_int_init_list = init_list;
    CCircularBufferExt<std::string> b_int_construct_1 = CCircularBufferExt<std::string>();
    CCircularBufferExt<std::string> b_int_construct_2 = CCircularBufferExt<std::string>(n, x);
    CCircularBufferExt<std::string> b_int_construct_3 = CCircularBufferExt<std::string>(init_vector.begin(), init_vector.end());
    CCircularBufferExt<std::string> b_int_construct_4 = CCircularBufferExt<std::string>(n);
    CCircularBufferExt<std::string> b_copy = b_int_init_list;

    ASSERT_TRUE(std::equal(b_int_init_list.begin(), b_int_init_list.end(), init_list.begin(), init_list.end()));
    ASSERT_EQ(b_int_construct_1.size(), 0);
    ASSERT_EQ(b_int_construct_2.size(), n);
    for(auto i : b_int_construct_2){
        ASSERT_EQ(i, x);
    }
    ASSERT_TRUE(std::equal(b_int_construct_3.begin(), b_int_construct_3.end(), init_vector.begin(), init_vector.end()));
    ASSERT_TRUE(std::equal(b_copy.begin(), b_copy.end(), b_int_init_list.begin(), b_int_init_list.end()));
    ASSERT_EQ(b_int_construct_4.size(), 0);
    ASSERT_EQ(b_int_construct_4.capacity(), n * 2);
}

TEST(CCircularBuffer, CycleTest){
    CCircularBuffer<std::string> buff = {"1", "2", "3", "4", "5", "6", "7"};

    for(int i = 0; i < buff.size() * 2; i++){
        ASSERT_EQ(buff[i], buff[i % buff.size()]);
    }
}

TEST(CCircularBufferExt, CycleTest){
    CCircularBufferExt<std::string> buff = {"1", "2", "3", "4", "5", "6", "7"};

    for(int i = 0; i < buff.size() * 2; i++){
        ASSERT_EQ(buff[i], buff[i % buff.size()]);
    }
}

TEST(CCircularBuffer, EraseTest){
    CCircularBuffer<std::string> buff = {"1", "2", "3", "4", "5", "6", "7"};

    buff.erase(buff.begin() + 1);
    ASSERT_EQ(buff.size(), 6);
    ASSERT_EQ(buff[0], "1");
    ASSERT_EQ(buff[1], "3");
    ASSERT_EQ(buff[2], "4");
    ASSERT_EQ(buff[3], "5");
    ASSERT_EQ(buff[4], "6");
    ASSERT_EQ(buff[5], "7");

    buff.erase(buff.begin() + 2, buff.end());

    ASSERT_EQ(buff.size(), 2);

    ASSERT_EQ(buff[0], "1");
    ASSERT_EQ(buff[1], "3");
}

TEST(CCircularBufferExt, EraseTest){
    CCircularBufferExt<std::string> buff = {"1", "2", "3", "4", "5", "6", "7"};

    buff.erase(buff.begin() + 1);
    ASSERT_EQ(buff.size(), 6);
    ASSERT_EQ(buff[0], "1");
    ASSERT_EQ(buff[1], "3");
    ASSERT_EQ(buff[2], "4");
    ASSERT_EQ(buff[3], "5");
    ASSERT_EQ(buff[4], "6");
    ASSERT_EQ(buff[5], "7");

    buff.erase(buff.begin() + 2, buff.end());

    ASSERT_EQ(buff.size(), 2);

    ASSERT_EQ(buff[0], "1");
    ASSERT_EQ(buff[1], "3");
}

TEST(CCircularBuffer, PushBackTest){
    CCircularBuffer<std::string> buff = CCircularBuffer<std::string>(5);

    buff.push_back("123");
    ASSERT_EQ(buff.size(), 1);
    ASSERT_EQ(*(buff.end() - 1), "123");

    buff.clear();

    for(int i = 0; i < 5; i++){
        buff.push_back(std::to_string(i));
    }

    for(int i = 0; i < 5; i++){
        ASSERT_EQ(buff[i], std::to_string(i));
    }

    buff.push_back("5");

    ASSERT_EQ(buff[5], "5");
}

TEST(CCircularBufferExt, PushBackTest){
    CCircularBufferExt<std::string> buff = CCircularBufferExt<std::string>(5);

    for(int i = 0; i < 5; i++){
        buff.push_back(std::to_string(i));
    }

    for(int i = 0; i < 5; i++){
        ASSERT_EQ(buff[i], std::to_string(i));
    }

    buff.push_back("7");

    ASSERT_EQ(*(buff.end() - 1), "7");
}

TEST(CCircularBufferExt, AssignTest){
    CCircularBufferExt<std::string> buff = CCircularBufferExt<std::string>();
    std::vector<std::string> init_vector = {"1", "2", "1231", "sadf;;la"};
    std::initializer_list<std::string> init_list = {";d;mfma", "kdffmvfmk", "wf;;a;slf"};

    buff.assign(init_list);
    ASSERT_TRUE(std::equal(buff.begin(), buff.end(), init_list.begin(), init_list.end()));

    buff.assign(init_vector.begin(), init_vector.end());
    ASSERT_TRUE(std::equal(buff.begin(), buff.end(), init_vector.begin(), init_vector.end()));

    buff.assign(5, "asd");
    ASSERT_EQ(buff.size(), 5);
    for(auto i : buff){
        ASSERT_EQ(i, "asd");
    }
}

TEST(CCircularBuffer, AssignTest){
    CCircularBuffer<std::string> buff = CCircularBuffer<std::string>(5);
    std::vector<std::string> init_vector = {"1", "2", "1231", "sadf;;la"};
    std::initializer_list<std::string> init_list = {";d;mfma", "kdffmvfmk", "wf;;a;slf"};

    buff.assign(init_vector.begin(), init_vector.end());
    ASSERT_TRUE(std::equal(buff.begin(), buff.end(), init_vector.begin(), init_vector.end()));

    buff.assign(init_list);
    ASSERT_TRUE(std::equal(buff.begin(), buff.end(), init_list.begin(), init_list.end()));

    ASSERT_ANY_THROW(buff.assign(10, "a"));
}

TEST(CCircularBuffer, SwapTest){
    CCircularBuffer<std::string> buff1 = { "a", "b", "c", "d" };
    CCircularBuffer<std::string> buff1_prev = buff1;
    CCircularBuffer<std::string> buff2 = { "1", "2", "3", "4", "5" };
    CCircularBuffer<std::string> buff2_prev = buff2;

    swap(buff1, buff2);

    ASSERT_TRUE(std::equal(buff1.begin(), buff1.end(), buff2_prev.begin(), buff2_prev.end()));
    ASSERT_TRUE(std::equal(buff2.begin(), buff2.end(), buff1_prev.begin(), buff1_prev.end()));

    swap(buff1, buff2);

    ASSERT_TRUE(std::equal(buff1.begin(), buff1.end(), buff1_prev.begin(), buff1_prev.end()));
    ASSERT_TRUE(std::equal(buff2.begin(), buff2.end(), buff2_prev.begin(), buff2_prev.end()));
}

TEST(CCircularBufferExt, SwapTest){
    CCircularBufferExt<std::string> buff1 = { "a", "b", "c", "d" };
    CCircularBufferExt<std::string> buff1_prev = buff1;
    CCircularBufferExt<std::string> buff2 = { "1", "2", "3", "4", "5" };
    CCircularBufferExt<std::string> buff2_prev = buff2;

    swap(buff1, buff2);

    ASSERT_TRUE(std::equal(buff1.begin(), buff1.end(), buff2_prev.begin(), buff2_prev.end()));
    ASSERT_TRUE(std::equal(buff2.begin(), buff2.end(), buff1_prev.begin(), buff1_prev.end()));

    swap(buff1, buff2);

    ASSERT_TRUE(std::equal(buff1.begin(), buff1.end(), buff1_prev.begin(), buff1_prev.end()));
    ASSERT_TRUE(std::equal(buff2.begin(), buff2.end(), buff2_prev.begin(), buff2_prev.end()));
}

TEST(CCircularBufferExt, InseertTest){
    CCircularBufferExt<std::string> buff = {"1", "3", "4", "5"};

    buff.insert(buff.begin() + 1, "2");

    for(int i = 0; i < 5; i++){
        ASSERT_EQ(buff[i], std::to_string(i + 1));
    }

    buff.assign({"1", "4", "5"});

    buff.insert(buff.begin() + 1, { "2", "3" });

    for(int i = 0; i < 5; i++){
        ASSERT_EQ(buff[i], std::to_string(i + 1));
    }

    buff.assign({"1", "4", "5"});

    std::vector<std::string> insert_vector = {"2", "3"};

    buff.insert(buff.begin() + 1, insert_vector.begin(), insert_vector.end());

    for(int i = 0; i < 5; i++){
        ASSERT_EQ(buff[i], std::to_string(i + 1));
    }

    buff.assign({"a", "a", "a"});

    buff.insert(buff.begin() + 2, 5, "a");

    ASSERT_EQ(buff.size(), 8);
    for(auto i : buff){
        ASSERT_EQ(i, "a");
    }
}