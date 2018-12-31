from netifaces import interfaces, AF_INET, ifaddresses


def get_valid_ips():
    ip_dictionary = {}
    print("Available ips to start server:")
    index = 0
    for ifaceName in interfaces():
        for address_list in [address for type_, address in ifaddresses(ifaceName).items() if
                             type_ == AF_INET]:
            for ip_address in address_list:
                ip_dictionary[index] = ip_address['addr']
                print(str(index) + ": " + ip_dictionary[index])
                index += 1

    return ip_dictionary


def user_selects_ip():
    ip_dictionary = get_valid_ips()

    while True:
        choice = int(input("Choose an IP index from the list above: "))
        if choice not in ip_dictionary.keys():
            print("Chosen an invalid index, try again.")
        else:
            selected_ip = ip_dictionary[choice]
            break

    return selected_ip


def get_valid_protocols():
    protocol_dictionary = {0: 'tcp', 1: 'udp'}
    index = 0
    for protocol_type in protocol_dictionary:
        print(str(index) + ": " + protocol_dictionary[index])
        index += 1

    return protocol_dictionary


def user_selects_protocol():
    protocol_dictoniary = get_valid_protocols()

    while True:
        choice = int(input("Choose an Protocol index from the list above: "))
        if choice not in protocol_dictoniary:
            print("Chosen an invalid index, try again.")
        else:
            selected_protocol = protocol_dictoniary[choice]
            break

    return selected_protocol
