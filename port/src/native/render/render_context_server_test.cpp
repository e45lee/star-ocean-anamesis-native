// Differential test of RenderContextServer's bump allocators (render_context_server.cpp) against the
// 3.7.0 guest: two private servers over the same (fake) pools, the same requests, the results and the
// objects compared after each; past the end of a pool (null, the counter left beyond the count), both
// light-context buffers, n = 0.
#include <cstring>

#include "native/common/test.h"
#include "native/render/render_layout.h"

namespace soa::native::render {

NATIVE_TEST("render/context-server-alloc") {
    alignas(16) RenderContextServer g{}, n{};
    g.m_batches = reinterpret_cast<RenderContextBatch*>(0x100000000ull);
    g.m_batchCount = 300;
    g.m_batchLites = reinterpret_cast<u32*>(0x200000000ull);
    g.m_batchLiteCount = 1000;
    g.m_lightContexts[0] = reinterpret_cast<LightContext*>(0x300000000ull);
    g.m_lightContexts[1] = reinterpret_cast<LightContext*>(0x300000000ull + 50 * sizeof(LightContext));
    g.m_lightContextCount = 50;
    std::memcpy(&n, &g, sizeof n);
    for (int k = 0; k < 400; k++) {
        const int which = t.rand_int(0, 2);
        const s32 cnt = k % 50 == 7 ? 0 : t.rand_int(1, 9);
        if (k == 200) g.m_bufferIndex = n.m_bufferIndex = 1;
        u64 gr, nr;
        if (which == 0) {
            gr = t.call("_ZN4Aska19RenderContextServer14GetRenderBatchEi", {(u64)&g, (u64)cnt});
            nr = (u64)n.GetRenderBatch(cnt);
        } else if (which == 1) {
            gr = t.call("_ZN4Aska19RenderContextServer18GetRenderBatchLiteEi", {(u64)&g, (u64)cnt});
            nr = (u64)n.GetRenderBatchLite(cnt);
        } else {
            gr = t.call("_ZN4Aska19RenderContextServer15GetLightContextEi", {(u64)&g, (u64)cnt});
            nr = (u64)n.GetLightContext(cnt);
        }
        if (gr != nr || std::memcmp(&g, &n, sizeof g) != 0) {
            t.fail("request %d (pool %d, n %d): result native %#llx guest %#llx, objects %s", k, which, cnt, (unsigned long long)nr,
                   (unsigned long long)gr, std::memcmp(&g, &n, sizeof g) ? "differ" : "equal");
            break;
        }
    }
    t.expect_eq(g.m_batchUsed > g.m_batchCount, true, "a pool taken past its end");
}

}  // namespace soa::native::render
