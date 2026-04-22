#include <cstdint>

enum class HIDKey : uint8_t {
    // Letters (0x04 - 0x1D)
    A = 0x04, B = 0x05, C = 0x06, D = 0x07, E = 0x08, F = 0x09, G = 0x0A,
    H = 0x0B, I = 0x0C, J = 0x0D, K = 0x0E, L = 0x0F, M = 0x10, N = 0x11,
    O = 0x12, P = 0x13, Q = 0x14, R = 0x15, S = 0x16, T = 0x17, U = 0x18,
    V = 0x19, W = 0x1A, X = 0x1B, Y = 0x1C, Z = 0x1D,

    // Digits (0x1E - 0x27)
    Digit1 = 0x1E, Digit2 = 0x1F, Digit3 = 0x20, Digit4 = 0x21, Digit5 = 0x22,
    Digit6 = 0x23, Digit7 = 0x24, Digit8 = 0x25, Digit9 = 0x26, Digit0 = 0x27,

    // Common Controls & Punctuation
    Enter      = 0x28,
    Escape     = 0x29,
    Backspace  = 0x2A,
    Tab        = 0x2B,
    Spacebar   = 0x2C,
    Minus      = 0x2D, // - and _
    Equal      = 0x2E, // = and +
    LeftBrace  = 0x2F, // [ and {
    RightBrace = 0x30, // ] and }
    Backslash  = 0x31, // \ and |
    Semicolon  = 0x33, // ; and :
    Quote      = 0x34, // ' and "
    Grave      = 0x35, // ` and ~
    Comma      = 0x36, // , and <
    Dot        = 0x37, // . and >
    Slash      = 0x38  // / and ?
};

// Modifier Bits (Sent in a separate byte in the HID report)
enum class HIDModifier : uint8_t {
    LeftControl  = 1 << 0,
    LeftShift    = 1 << 1,
    LeftAlt      = 1 << 2,
    LeftGUI      = 1 << 3, // Windows/Command key
    RightControl = 1 << 4,
    RightShift   = 1 << 5,
    RightAlt     = 1 << 6,
    RightGUI     = 1 << 7
};