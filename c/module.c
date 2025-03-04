#include <stdlib.h>
#include <janet.h>
#include "md5.h"

JANET_FN(cfun_MD5_Init,
    "(md5/init)",
    "")
{
    janet_fixarity(argc, 0);
    MD5_CTX *ctx = calloc(1, sizeof(MD5_CTX));
    MD5_Init(ctx);
    return janet_wrap_pointer(ctx);
}

JANET_FN(cfun_MD5_Update,
    "(md5/update ctx bytes length)",
    "")
{
    janet_fixarity(argc, 2);
    MD5_CTX *ctx = janet_getpointer(argv, 0);
    JanetBuffer *buffer = janet_getbuffer(argv, 1);
    MD5_Update(ctx, buffer->data, buffer->count);
    return janet_wrap_nil();
}

JANET_FN(cfun_MD5_Final,
    "(md5/final ctx)",
    "")
{
    janet_fixarity(argc, 1);
    MD5_CTX *ctx = (MD5_CTX*)janet_getpointer(argv, 0);
    char result[16];
    MD5_Final(result, ctx);
    JanetBuffer *buffer = janet_buffer(16);
    janet_buffer_push_bytes(buffer, result, 16);
    free(ctx);
    return janet_wrap_buffer(buffer);
}

JANET_MODULE_ENTRY(JanetTable *env)
{
    JanetRegExt cfuns[] = {
        JANET_REG("init", cfun_MD5_Init),
        JANET_REG("update", cfun_MD5_Update),
        JANET_REG("final", cfun_MD5_Final),
        JANET_REG_END
    };
    janet_cfuns_ext(env, "md5", cfuns);
}