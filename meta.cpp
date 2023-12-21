//Compile-time implementation
//C++ 14




#include <array>
#include <iostream>




constexpr int C = 0;
constexpr int C_SHARP = 1;
constexpr int D = 2;
constexpr int D_SHARP = 3;
constexpr int E = 4;
constexpr int F = 5;
constexpr int F_SHARP = 6;
constexpr int G = 7;
constexpr int G_SHARP = 8;
constexpr int A = 9;
constexpr int A_SHARP = 10;
constexpr int B = 11;


constexpr const char* tone_to_string(int note) {
    switch(note) {
        case C:       return "C";
        case C_SHARP: return "C#";
        case D:       return "D";
        case D_SHARP: return "D#";
        case E:       return "E";
        case F:       return "F";
        case F_SHARP: return "F#";
        case G:       return "G";
        case G_SHARP: return "G#";
        case A:       return "A";
        case A_SHARP: return "A#";
        case B:       return "B";
        default:      return "";
    }
}


template<typename Row, std::size_t... I>
constexpr auto invert_helper(const Row& row, std::index_sequence<I...>) {
    constexpr auto n = sizeof...(I);
    const int first_note = row[0];
    return std::array<int, n>{((2 * first_note - row[I] + 12) % 12)...}; 
}


template<typename Row>
constexpr auto invert(const Row& row) {
    constexpr auto size = Row{}.size();
    return invert_helper(row, std::make_index_sequence<size>{});
}


template<int TargetNote, typename Row, std::size_t... I>
constexpr auto transpose_helper(const Row& row, std::index_sequence<I...>) {
    constexpr auto n = sizeof...(I);
    const int first_note = row[0];
    return std::array<int, n>{((row[I] + TargetNote - first_note + 12) % 12)...};
}


template<int TargetNote, typename Row>
constexpr auto transpose(const Row& row) {
    constexpr auto size = Row{}.size();
    return transpose_helper<TargetNote>(row, std::make_index_sequence<size>{});
}


template<int... TargetNotes, typename Row>
constexpr auto multi_transpose(const Row& row) {
    return std::array<std::array<int, Row{}.size()>, sizeof...(TargetNotes)>{transpose<TargetNotes>(row)...};
}


static constexpr std::array<int, 12> row{ C_SHARP, C, F_SHARP, D_SHARP, G_SHARP, E, B, F, A, A_SHARP, G, D };
static constexpr std::array<int, 12> inv = invert(row);
static constexpr auto schoenbergian_square = 
    multi_transpose<inv[0], inv[1], inv[2], inv[3],
                    inv[4], inv[5], inv[6], inv[7],
                    inv[8], inv[9], inv[10],inv[11]>(row);


int main() {

    std::cout << "Original row: ";
    for (const auto& n : row) {
        std::cout << tone_to_string(n) << ' ';
    }
    std::cout << '\n' << '\n';
    std::cout << "Schoenbergian square:";
    std::cout << '\n';

    for (const auto& r : schoenbergian_square) {     
        for (const auto& n : r) {
            std::cout << tone_to_string(n) << ' ';
        }
        std::cout << '\n';
    }
}
