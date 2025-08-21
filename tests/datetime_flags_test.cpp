#include <cstdint>
#include <cstring>
#include <cassert>
#include <vector>
#include <string>
#include <ctime>
#include <cctype>
#include <iostream>

typedef unsigned char uchar;

struct DVEntry {
    std::string value;
    bool extractDate(struct tm* out, int* week_number = nullptr,
                     int* dst_offset_minutes = nullptr, bool* leap_year = nullptr);
};

using std::string; using std::vector;

static int char2int(char c){
    if ('0'<=c && c<='9') return c-'0';
    if ('a'<=c && c<='f') return c-'a'+10;
    if ('A'<=c && c<='F') return c-'A'+10;
    return -1;
}

bool hex2bin(const string& src, vector<uchar>* target){
    const char* s = src.c_str();
    while (*s && s[1]){
        if (*s==' '||*s=='#'||*s=='|'||*s=='_') s++;
        else {
            int hi=char2int(*s); int lo=char2int(s[1]);
            if (hi<0||lo<0) return false;
            target->push_back(hi*16+lo); s+=2;
        }
    }
    return true;
}

bool extractDate(uchar hi, uchar lo, struct tm* date){
    int day = (0x1f) & lo;
    int year1 = ((0xe0) & lo) >> 5;
    int month = (0x0f) & hi;
    int year2 = ((0xf0) & hi) >> 1;
    int year = (2000 + year1 + year2);
    date->tm_mday = day;
    date->tm_mon = month - 1;
    date->tm_year = year - 1900;
    if (month > 12) return false;
    return true;
}

bool extractTime(uchar hi, uchar lo, struct tm* date){
    int min = (0x3f) & lo;
    int hour = (0x1f) & hi;
    date->tm_min = min;
    date->tm_hour = hour;
    if (min > 59) return false;
    if (hour > 23) return false;
    return true;
}

bool DVEntry::extractDate(struct tm* out, int* week_number, int* dst_offset_minutes, bool* leap_year){
    memset(out,0,sizeof(*out));
    out->tm_isdst = -1;
    vector<uchar> v; hex2bin(value,&v);
    bool ok=true;
    if (v.size()==2){
        ok &= ::extractDate(v[1],v[0],out);
    } else if (v.size()==4){
        ok &= ::extractDate(v[3],v[2],out);
        ok &= ::extractTime(v[1],v[0],out);
    } else if (v.size()==6){
        ok &= ::extractDate(v[4],v[3],out);
        ok &= ::extractTime(v[2],v[1],out);
        int sec = (0x3f) & v[0];
        out->tm_sec = sec;
        int dow = (v[2] >> 5) & 0x07;
        out->tm_wday = dow;
        if (week_number) *week_number = v.size()>5 ? (v[5] & 0x3f) : 0;
        int dst_code = (v[0] >> 6) & 0x03;
        if (dst_offset_minutes){
            int offset=0; switch(dst_code){case 1: offset=60; break; case 2: offset=-60; break; default: offset=0;}
            *dst_offset_minutes = offset;
        }
        if (dst_code==1) out->tm_isdst=1; else out->tm_isdst=0;
        bool leap = ((v[1] >> 6) & 0x01)!=0;
        if (leap_year) *leap_year = leap;
    }
    return ok;
}

int main(){
    DVEntry dve; dve.value = "5E5B4E05330A"; // Tue week10 dst +60 leap
    struct tm tm{}; int week=0; int dst=0; bool leap=false;
    bool ok = dve.extractDate(&tm,&week,&dst,&leap);
    assert(ok);
    assert(tm.tm_year==124);
    assert(tm.tm_mon==2);
    assert(tm.tm_mday==5);
    assert(tm.tm_hour==14);
    assert(tm.tm_min==27);
    assert(tm.tm_sec==30);
    assert(tm.tm_wday==2);
    assert(week==10);
    assert(dst==60);
    assert(leap);

    DVEntry dve2; dve2.value = "AD3B17FF2C34"; // Sun week52 dst -60 not leap
    struct tm tm2{}; week=0; dst=0; leap=true;
    ok = dve2.extractDate(&tm2,&week,&dst,&leap);
    assert(ok);
    assert(tm2.tm_year==123);
    assert(tm2.tm_mon==11);
    assert(tm2.tm_mday==31);
    assert(tm2.tm_hour==23);
    assert(tm2.tm_min==59);
    assert(tm2.tm_sec==45);
    assert(tm2.tm_wday==0);
    assert(week==52);
    assert(dst==-60);
    assert(!leap);
    std::cout << "All tests passed\n";
    return 0;
}
