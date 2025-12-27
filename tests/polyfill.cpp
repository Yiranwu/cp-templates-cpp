#include <cstddef>

// Polyfill for missing symbol in AppleClang 16 libc++ with -fexperimental-library
// We define this in a separate file to avoid conflicting with the header declaration
// which might have attributes we can't easily reproduce.
// The linker only cares about the symbol name.

namespace std { inline namespace __1 {
    size_t __hash_memory(void const* ptr, size_t len) noexcept {
        size_t hash = 5381;
        const char* p = static_cast<const char*>(ptr);
        while (len--) {
            hash = ((hash << 5) + hash) + *p++; /* hash * 33 + c */
        }
        return hash;
    }
}}
