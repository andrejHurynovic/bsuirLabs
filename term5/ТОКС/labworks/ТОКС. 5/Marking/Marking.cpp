//
//  Marking.cpp
//  main
//
//  Created by Andrej Hurynovič on 15.11.21.
//

#include "Marking.hpp"

void Marking::start() {
    this->set_start_delimiter(1234);
    this->set_ending_delimiter(4321);
    this->set_inter_frame_gap();
}

void Marking::set_source_adress(const std::string &adress) {
    memcpy(this->value.SourceAddress, adress.c_str(), sizeof(this->value.SourceAddress));
}

std::string Marking::get_source_adress() const {
    return this->value.SourceAddress;
}

void Marking::set_destination_address(const std::string &adress) {
    memcpy(this->value.DestinationAddress, adress.c_str(), sizeof(this->value.DestinationAddress));
}

std::string Marking::get_destination_adress() const {
    return this->value.DestinationAddress;
}

void Marking::set_priority(const unsigned int &priority) {
    this->value.set_priority_bit(priority);
}

unsigned int Marking::get_priority() const {
    return this->value.get_priority_bit();
}

void Marking::set_token(const unsigned int &token) {
    this->value.set_token_bit(token);
}

unsigned int Marking::get_token() const {
    return this->value.get_token_bit();
}

void Marking::set_reservation(const unsigned int &reserv) {
    this->value.set_reservation_bit(reserv);
}

unsigned int Marking::get_reservation() const {
    return this->value.get_reservation_bit();
}

void Marking::set_frame_status(const unsigned int &frame) {
    this->value.set_frame_status(frame);
}

unsigned int Marking::get_frame_status() const {
    return this->value.get_frame_status();
}

void Marking::set_id(const unsigned int &id) noexcept {
    this->value.Id = id;
}

unsigned int Marking::get_id() const noexcept {
    return this->value.Id;
}

void Marking::set_start_delimiter(const unsigned int &delimiter) {
    this->value.StartingDelimiter = delimiter;
}

unsigned int Marking::get_start_delimiter() const {
    return this->value.StartingDelimiter;
}

void Marking::set_ending_delimiter(const unsigned int &delimiter) {
    this->value.EndingDelimiter = delimiter;
}

unsigned int Marking::get_ending_delimiter() const {
    return this->value.EndingDelimiter;
}

void Marking::set_frame_check_sequence(const unsigned int &size) {
    this->value.FrameCheckSequence = sizeof(this->value);
}

size_t Marking::get_frame_check_sequence() const {
    return this->value.FrameCheckSequence;
}

void Marking::set_inter_frame_gap() {

}

void Marking::set_regime(const unsigned int &regime) {
    this->value.Regime = regime;
}

unsigned int Marking::get_regime() const {
    return this->value.Regime;
}

const char* Marking::get_data() const noexcept {
    return this->value.Data;
}
