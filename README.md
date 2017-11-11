<p align="center"><img src="https://assets-cdn.github.com/favicon.ico" width=24 height=24/>
<p align="center"><a href="git clone https://github.com/deltaxflux/airsniff-ngi">Airsniff-ng</a>,is an intrusion detector,spoofer, sniffer and network analyzer. </p>

---

# Airsniff-ng

Airsniff-ng is an intrusion detector,spoofer, sniffer and network analyzer.

### Getting started
Only thing you have to do is
```
git clone https://github.com/deltaxflux/airsniff-ng
cd airsniff-ng
make
./airsniff-ng
```

## Features
* ARP Spoofer
* Speedport password generator
* Command completion with tab
* History for fast completion
* Config files

### Install
The installation is very simple use your favorite package manager e.g. apt or apt-get and install all required packages before running the curl script.

#### On debian
```
sudo apt-get install g++ gcc boost
```

#### On arch
```
sudo pacman -S g++ gcc boost
```

### Tutorials
#### Arp spoofing
Arp spoofing is even simpler with airsniff-ng. You can use the arp_poison module. For that use following commands:
```
./airsniff-ng
set_gateway_ip [gateway-ip]
set_target_ip [target-ip]
set_interface [interface]
arp_poison 
```

##### Screenshots
![alt text](https://i.imgur.com/8Uj98MD.png)

#### Speedport wordlist generator
The speedport password generator generate a common sequenze for speedport routers. It reduces the amount of combinination greatly. Here is a quick calculation: <br>
Possibile combinations: 8^93 = 9.73e83<br>
Reduced amount of combinations: 1 million <br>
<br>
To use this module use following commands:
```
set_ssid "WLAN-9A3907"
set_bssid "00:12:BF:9A:39:41"
gen_speedport_w500 
```

##### Screenshots
![alt text](https://i.imgur.com/qQF9quT.png)

##### Using wordlists
This wordlist is saved in wordlist/speedport-w500.txt. You now can use, to bruteforce the combinations:
`àircrack -w [wordlist] cap`

### Development
We try always to improve the dotfiles. If you want to constibute create a pull request.
<br>
<br>
 [![](https://img.shields.io/badge/Workflow-gitflow--branching--model-81A1C1.svg?style=flat-square)](http://nvie.com/posts/a-successful-git-branching-model) 

### Contribution

Please report issues/bugs, feature requests and suggestions for improvements to the [issue tracker](https://github.com/deltaxflux/airsniff-ng/issues).

<p align="center"><img src="https://cdn.rawgit.com/arcticicestudio/nord/develop/src/assets/banner-footer-mountains.svg" /></p>
<p align="center"><a href="http://www.apache.org/licenses/LICENSE-2.0"><img src="https://img.shields.io/badge/License-Apache_2.0-5E81AC.svg?style=flat-square"/></a> <a href="https://creativecommons.org/licenses/by-sa/4.0"><img src="https://img.shields.io/badge/License-CC_BY--SA_4.0-5E81AC.svg?style=flat-square"/></a></p>

