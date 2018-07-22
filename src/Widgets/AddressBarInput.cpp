#include "AddressBarInput.h"
#include "AddressBar.h"

AddressBarInput::AddressBarInput(AddressBar* parent): QLineEdit(parent), popup(this), bar(parent) {
};