#include <iostream>
#include <vector>
#include <map>
#include <fstream>
/*
def genprimes(limit):  # derived from
# Code by David Eppstein, UC Irvine, 28 Feb 2002
D = {}  # http://code.activestate.com/recipes/117119/
q = 2

while q <= limit:
if q not in D:
yield q
D[q * q] = [q]
else:
for p in D[q]:
D.setdefault(p + q, []).append(p)
del D[q]
q += 1
*/
template <typename S>
std::ostream& operator<<(std::ostream& os,
                    const std::vector<S>& vector)
{
    // Printing all the elements
    // using <<
    for (auto element : vector) {
        os << element << " ";
    }
    return os;
}

auto genprimes(u_int32_t limit){
    std::vector<u_int32_t> primes;
    std::map<u_int32_t , std::vector<u_int32_t>> composite_map;
    u_int32_t q = 2;
    while(q <= limit){
        if (auto search = composite_map.find(q); search != composite_map.end()){
            for(auto p : composite_map[q]){
                int_fast64_t pq = p+q;
                if (auto search_pq = composite_map.find(pq); search_pq != composite_map.end()){
                    composite_map[pq].push_back(p);
                } else {
                    composite_map[pq] = {p};
                }
            }
            composite_map.erase(q);
        } else {
            primes.push_back(q);
            composite_map[q*q] = {q};
        }
        q += 1;
    }
    return primes;
}



int main() {

    auto start = std::chrono::steady_clock::now();
    int lim = 100000000;
    std::cout << "Generating primes up to: " << lim << std::endl;
    //std::cout << genprimes(lim) << std::endl;
    auto primes = genprimes(lim);
    std::ofstream file("primes.bin", std::ios::binary);
    for(auto p : primes){
        file.write( (char *)&p, sizeof(p));
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end- start;
    file.close();

    std::cout << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;


    return 0;
}
