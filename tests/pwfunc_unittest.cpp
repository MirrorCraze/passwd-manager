#include "gtest/gtest.h"
#include "sha256.h"
#include "pwfunc.h"
#include "test_utils.h"   //provide gen_random for random strings
#include "test_settings.cpp"

TEST(PWFUNCClass, input_output){
    sha256* hash = new sha256();
    PwFunc pwf = PwFunc(hash);
    
    for(int i=0; i < SET_MAX_PW_LEN; i++){
        std::string p = gen_random_string(i);
        Bytes tmp = pwf.chainhash(p, SET_PW_ITERS);
        EXPECT_EQ(SHA256_DIGEST_LENGTH, tmp.getLen());
        Bytes tmp2 = pwf.chainhashWithConstantSalt(p, SET_PW_ITERS);
        EXPECT_EQ(SHA256_DIGEST_LENGTH, tmp2.getLen());
        Bytes tmp3 = pwf.chainhashWithConstantSalt(p, SET_PW_ITERS, gen_random_string(100));
        EXPECT_EQ(SHA256_DIGEST_LENGTH, tmp3.getLen());
        Bytes tmp4 = pwf.chainhashWithCountSalt(p, SET_PW_ITERS);
        EXPECT_EQ(SHA256_DIGEST_LENGTH, tmp4.getLen());
        Bytes tmp5 = pwf.chainhashWithCountSalt(p, SET_PW_ITERS, 100);
        EXPECT_EQ(SHA256_DIGEST_LENGTH, tmp5.getLen());
        Bytes tmp6 = pwf.chainhashWithCountAndConstantSalt(p, SET_PW_ITERS);
        EXPECT_EQ(SHA256_DIGEST_LENGTH, tmp6.getLen());
        Bytes tmp7 = pwf.chainhashWithCountAndConstantSalt(p, SET_PW_ITERS, 100, gen_random_string(100));
        EXPECT_EQ(SHA256_DIGEST_LENGTH, tmp7.getLen());
    }

    delete hash;
}

TEST(PWFUNCClass, concistency){
    sha256* hash = new sha256();
    PwFunc pwf = PwFunc(hash);
    
    for(int i=0; i < SET_MAX_PW_LEN; i++){
        std::string p = gen_random_string(i);
        std::string s = gen_random_string(100);
        EXPECT_EQ(pwf.chainhash(p, SET_PW_ITERS), pwf.chainhash(p, SET_PW_ITERS));
        EXPECT_EQ(pwf.chainhashWithConstantSalt(p, SET_PW_ITERS), pwf.chainhashWithConstantSalt(p, SET_PW_ITERS));
        EXPECT_EQ(pwf.chainhashWithConstantSalt(p, SET_PW_ITERS, s), pwf.chainhashWithConstantSalt(p, SET_PW_ITERS, s));
        EXPECT_EQ(pwf.chainhashWithCountSalt(p, SET_PW_ITERS), pwf.chainhashWithCountSalt(p, SET_PW_ITERS));
        EXPECT_EQ(pwf.chainhashWithCountSalt(p, SET_PW_ITERS, 100), pwf.chainhashWithCountSalt(p, SET_PW_ITERS, 100));
        EXPECT_EQ(pwf.chainhashWithCountAndConstantSalt(p, SET_PW_ITERS), pwf.chainhashWithCountAndConstantSalt(p, SET_PW_ITERS));
        EXPECT_EQ(pwf.chainhashWithCountAndConstantSalt(p, SET_PW_ITERS, 100, s), pwf.chainhashWithCountAndConstantSalt(p, SET_PW_ITERS, 100, s));
    }

    delete hash;
}

TEST(PWFUNCClass, correctness){
    sha256* hash = new sha256();
    PwFunc pwf = PwFunc(hash);
    std::string p = "Password";
    std::string s = "salt";
    std::string phash = "e7cf3ef4f17c3999a94f2c6f612e8a888e5b1026878e4e19398b23bd38ec221a";
    std::string phashs = "c990daffb01d8091e8af9a91227370cfa6f7d1c44e7ab062940486c57676418c";

    std::string phashchain = "7be274414bc74dd332d5a0fafc94e5a1da20d091553260a2c1790a82529380f6";
    for (auto & c: phashchain) c = toupper(c);
    std::string phashchaincnoargs = "cdce8ae59e9719084a7131fc06587b57149d9dd4597ef7e1227be8cb5c978c76";
    for (auto & c: phashchaincnoargs) c = toupper(c);
    std::string phashchainc = "93e7864f8588196472da975c85499afa8fd93faaec4cd0e612fc8f78b8e4515d";
    for (auto & c: phashchainc) c = toupper(c);
    std::string phashchaincountnoargs = "7130c6b356a8e27894f5853d8f92efe9569280c60a3c2f4a5174cc03490d2aa4";
    for (auto & c: phashchaincountnoargs) c = toupper(c);
    std::string phashchaincount = "d347755d295b474bfd8a9d48134c523fadccf6b67633253c16784aa1f66dc244";
    for (auto & c: phashchaincount) c = toupper(c);
    std::string phashchainccount = "278979129cd421d273d7e2fa3ac8721004c6c49da2c7f9f4d451da2267de746a";
    for (auto & c: phashchainccount) c = toupper(c);
    std::string phashchainccountnoargs = "a2930b8c9f4e5d9c10d06534b4cf8b204fbfba8ca12ef4f3aa0092f7ac707269";
    for (auto & c: phashchainccountnoargs) c = toupper(c);
    
    EXPECT_EQ(phashchain, toHex(pwf.chainhash(p, 3)));
    EXPECT_EQ(phashchaincnoargs, toHex(pwf.chainhashWithConstantSalt(p, 3)));
    EXPECT_EQ(phashchainc, toHex(pwf.chainhashWithConstantSalt(p, 3, s)));
    EXPECT_EQ(phashchaincountnoargs, toHex(pwf.chainhashWithCountSalt(p, 3)));
    EXPECT_EQ(phashchaincount, toHex(pwf.chainhashWithCountSalt(p, 3, 100)));
    EXPECT_EQ(phashchainccountnoargs, toHex(pwf.chainhashWithCountAndConstantSalt(p, 3)));
    EXPECT_EQ(phashchainccount, toHex(pwf.chainhashWithCountAndConstantSalt(p, 3, 100, s)));

    delete hash;
}
