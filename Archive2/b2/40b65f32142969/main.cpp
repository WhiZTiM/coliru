
void Ctl4xxNmeaParser::parseGAGSV(const std::string&, const token_list_t& tokens)
{
    if (tokens.size() < 4)
		throw std::runtime_error("Require at least 4 tokens for GAGSV");

	// Up to three $GAGSV messages can be sent at a time.
	// Each may contain information for up to four satellites.
	// This gives a total of 12 "in view" satellites supported at a time.
	//
	// We track the values we're given as "number of messages" and
	// "sequence number" fields so that we only overwrite the GAGSV data when
	// we have it all.
	unsigned int number_messages   = fast_lexical_cast<unsigned int>(tokens[1]);
	unsigned int sequence_number   = fast_lexical_cast<unsigned int>(tokens[2]);
	unsigned int number_satellites = fast_lexical_cast<unsigned int>(tokens[3]);

	/*
		if (sequence_number == 1) {
			buffer_gpgsv = Ctl4xxData::gpgsv_t();
	}*/

	unsigned int number_satellites_this_message = 0;
	if (number_messages == 1)
		number_satellites_this_message = number_satellites;
	else if (number_messages > 1) {
		if (sequence_number < number_messages) {
			number_satellites_this_message = 4;
		}
		else {
			if (number_satellites % 4)
				number_satellites_this_message = number_satellites % 4;
			else
				number_satellites_this_message = 4;
		}
	}
	else throw std::runtime_error("Invalid number of messages stated in GAGSV");

	unsigned int num_tokens = 4 + (number_satellites_this_message * 4);
	if (tokens.size() < 4 + (number_satellites_this_message * 4)) {
		throw std::runtime_error(
			"Require " + boost::lexical_cast<std::string>(num_tokens) +
			" tokens for this GAGSV sequence"
		);
	}

	parseGPGSV(line, tokens);
}