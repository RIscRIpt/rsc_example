#include <iostream>
#include <conio.h>

#include <rsc/Card.h>
#include <rsc/Readers.h>
#include <rsc/Context.h>

std::ostream& operator<<(std::ostream &os, std::vector<BYTE> const &bytes) {
    // TODO: print bytes
}

std::ostream& operator<<(std::ostream &os, rsc::rAPDU const &rapdu) {
    return os << const_cast<rsc::rAPDU&>(rapdu).buffer();
}

int main() {
    try {
        rsc::Context context(SCARD_SCOPE_USER);
        rsc::Readers readers(context, SCARD_DEFAULT_READERS);
        rsc::Card card(context, readers.list().front());
        std::cout << card.atr();
        std::cout << card.transmit(rsc::cAPDU(0x00, 0xA4, 0x04, 0x00, { 0xA0, 0x00, 0x00, 0x00, 0x03, 0x10, 0x10 }));
    } catch (std::exception const &e) {
        std::cerr << e.what() << '\n';
        return -1;
    }
    return 0;
}
