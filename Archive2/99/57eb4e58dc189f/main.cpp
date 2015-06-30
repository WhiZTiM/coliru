// No, I am not responsible for the SCREAMING_CAPS.
std::map<std::string, nnf::CONTRACT_DESC>() contracts;
std::string line;
std::vector<std::string> fields;

// Number of columns in the CSV.
fields.reserve(69);

// Skip header.
std::getline(f, line);

while (std::getline(f, line)) {
    // If last character of line is 'Y', it means the record is deleted, don't bother parsing.
    if (line.size() > 1 && line[line.size() - 1] == 'Y') {
        continue;
    }

    fields.clear();
    boost::split(fields, line, boost::is_any_of("|"));

    if (fields.size() < 9) {
        throw; // TODO message
    }

    contracts.emplace(std::piecewise_construct,
        std::forward_as_tuple(std::move(fields[0])),
        // Can't move those
        std::forward_as_tuple(
            fields[2],
            fields[3],
            std::stoi(fields[6]),
            std::stoi(fields[7]),
            fields[8]
        ));
}