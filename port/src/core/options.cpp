// Run options (see options.h): filled from the command line only (main.cpp).
#include "core/options.h"

namespace soa {

namespace {
RunOptions g_options;
}  // namespace

const RunOptions& options() { return g_options; }
RunOptions& mutable_options() { return g_options; }

}  // namespace soa
