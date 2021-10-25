# :large_orange_diamond: netwhat &ensp; ![42Project Score](https://badge42.herokuapp.com/api/project/floogman/netwhat)

This project is an introduction to network problematics.

<br>

## :small_orange_diamond: Notes
### What is an IP address?
An `IP address` is a 32 bits ([IPv4](https://www.avast.com/c-ipv4-vs-ipv6-addresses)) unique address that identifies a device on the internet or a local network. IP stands for `"Internet Protocol"`, which is a set of rules governing the format of data sent via the internet or local network.<br>
IP addresses are normally expressed in `dotted-decimal` notation, with four numbers (or `octets`) separated by periods, such as 192.168.123.132.<br>
Each number can range from `0 to 255` and the full IP addressing range goes from `0.0.0.0 to 255.255.255.255`.

<br>

### Network Classes
IP addresses are divided into `classes`. The most common of them are classes `A`, `B`, and `C`. Classes D and E exist, but aren't used by end users. Each of the address classes has a different `default Netmask`. You can identify the class of an IP address by looking at its first octet.

Class | Leading Bits (Binary Notation) | Range | Netmask
:----:|:------------------------------:|:-----:|:-------:
**A** | 0 | 0.0.0.0 - 127.255.255.255 | 255.0.0.0
**B** | 10 | 128.0.0.0 - 191.255.255.255 | 255.255.0.0
**C** | 110 | 192.0.0.0 - 223.225.225.255 | 255.255.255.0
<br>

### What is a Netmask?
A Netmask is a `32-bit binary mask` used to divide an IP address into `subnets` and specify the network's available `hosts`.<br>
In a Netmask, two of the possible addresses, the `first` and `last`, are always pre-assigned and unavailable for custom assignment. They are the assigned `network address` (e.g. 255.255.255.`0`) and the the assigned `broadcast address` (e.g. 255.255.255.`255`) respectively. ***These two values cannot be used for IP address assignment.***

<br>

A simple formula can determine the `amount of networks` a netmask can support:
> 2^(netmask length - # of used segments) - 2

To determine the `number of hosts` a netmask is capable of supporting, use the following formula:
> 2^(# of zeroes) - 2

<br>

Class | Netmask Length | # of Networks | # of Hosts | Netmask
:----:|:--------------:|:-------------:|:----------:|:-------:
**A** | 8 | 126 | 16,777,214 | 255.0.0.0
**B** | 16 | 16,382 | 65,534 | 255.255.0.0
**C** | 24 | 2,097,150 | 254 | 255.255.255.0

<br>

### What is the subnet of an IP with Netmask?
***A subnet is the result of a Netmask being used to divide an IP address into two parts.***<br>
One part identifies the `host` (computer), the other part identifies the `network` to which it belongs.<br><br>
Converting an IP address into `binary notation` and lining it up with its corresponding `Netmask`, the network, and host portions of the address can be separated by performing a `bitwise AND` operation.

<br>

### Converting Dotted-decimal To Binary Notation
Each number in dotted-decimal notation represents an `octet` in `binary notation`. One octet consists of `8 bits` and each bit has the value of `2^n`. The rightmost (8th) has the value 2^0 and the leftmost (1st) has the value 2^7.

bit | 1st | 2nd | 3rd | 4th | 5th | 6th | 7th | 8th
:--:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:
**value** | **128** | **64** | **32** | **16** | **8** | **4** | **2** | **1**

<br>

A number in dotted-decimal notation is made up of the `sum` of the values of all `active bits` in the octet it represent:

octet | 1st | 2nd | 3rd | 4th
:----:|:---:|:---:|:---:|:---:
decimal | 192. | 168. | 123. | 132
| | 128 + 64 | 128 + 32 + 8 | 64 + 32 + 16 + 8 + 2 + 1 | 128 + 4
binary | 11000000. | 10101000. | 01111011. | 10000100

<br>

### Lining Up IP Address and Netmask

11000000.10101000.01111011.10000100 - 192.168.123.132 (IP address)<br>
11111111.11111111.11111111.00000000 - 255.255.255.0 (Netmask)

In the example above, the IP address is of class C (note the leading bits). Therefore, the first 24 bits (# of `1`'s in the Netmask) are identified as the network address. The last 8 bits (# of remaining `0`'s in the Netmask) are identified as the host address. Performing the `bitwise AND` operation gives you the following addresses:

11000000.10101000.01111011.00000000 - 192.168.123.0 (Network address)<br>
00000000.00000000.00000000.10000100 - 000.000.000.132 (Host address)

<br>

### Public and Private IPs
The main difference between public and private IP addresses is how far they reach, and what they’re connected to. A `public IP` address identifies you to the wider `internet` so that all the information you’re searching for can find you. A `private IP` address is used within a `private network` to connect securely to other devices within that same network.

<br>

|Private IPv4 Address Ranges|
|:----:|
|10.0.0.0 - 10.255.255.255|
|172.16.0.0 - 172.31.255.255|
|192.168.0.0 - 192.168.255.255|
<br>

### TCP vs. UDP
*Transmission Control Protocol* (`TCP`) and *User Datagram Protocol* (`UDP`) are `internet protocols` that transfer data. More specifically, TCP and UDP are both communication protocols and fall within the `transport layer` of the `OSI model`.<br>
A list of key differences between the two:<br>
TCP | UDP
:---:|:---:
connection-oriented | datagram-oriented
reliable, ordered, and error-checked delivery of packets | unreliable delivery of packets
slow | fast
does not support broadcasting | supports broadcasting

<br>

In summary: TCP is *slower* than UDP **but** more *reliable*.

<br>

### OSI Model
The `OSI model` serves as the vertical framework and standards that guide how information exchanges among cumputing systems. The seven layers of the OSI model are:
1. Physical (lowest)
2. Data Link
3. Network
4. Transport
5. Session
6. Presentation
7. Application (highest)

<br>

### DHCP
A `DHCP Server` can be a router or a server acting as a host. This is a networked device that automatically provides and assigns IP addresses, default gateway and other network parameters to client devices. It relies on the standart protocol known as *Dynamic Host Configuration Protocol* or `DHCP` to respond to broadcast quries by clients (such as a computer or a mobile device).

<br>

### DNS
The *Domain Name System* or `DNS` is a directory of names that match with IP addresses, allowing for the conversion between human readable domain names and computer readable IP addresses.

<br>

### Routing
`Routing` is the process of selecting a path across one or more networks to move packets of data from their source to their destination.

<br>

### Default Gateway
A `Default Gateway` is a node that enables a seamless connection between networks, allowing one device to talk to another device on a different network. It is called a 'default' gateway because it is the first and default route to take unless another option is activey requested.

<br>

## :small_orange_diamond: Resources
- [IP Address - Definition and Explanation](https://www.kaspersky.com/resource-center/definitions/what-is-an-ip-address)
- [Netmask](https://www.computerhope.com/jargon/n/netmask.htm)
- [Understanding TCP/IP Addressing and Subnetting Basics](https://docs.microsoft.com/en-us/troubleshoot/windows-client/networking/tcpip-addressing-and-subnetting)
- [Guide To Subnetting](https://www.softwaretestinghelp.com/subnet-mask-and-network-classes/)
- [TCP vs UDP](https://sectigostore.com/blog/tcp-vs-udp-whats-the-difference/)
- [DHCP](https://www.tek-tools.com/network/what-is-dhcp)
- [DNS](https://dnsmadeeasy.com/support/what-is-dns/)
- [Routing](https://www.webopedia.com/definitions/routing/)
- [Default Gateway](https://www.itpro.co.uk/network-internet/30327/what-is-a-default-gateway)
#### Practice
- [Netwhat Trainer](https://github.com/adblanc/netwhat42-train)
- [Netwhat Trainer (py)](https://github.com/abdlalisalmi/netwhat-trainer)
#### README
- [Markdown](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Multiple Consecutive Spaces in Markdown](https://steemit.com/markdown/@jamesanto/how-to-add-multiple-spaces-between-texts-in-markdown)
#### Attributions
- Dynamically generated badge by [badge42](https://github.com/JaeSeoKim/badge42)
