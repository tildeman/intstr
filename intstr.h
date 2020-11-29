//Integer (unsigned) string operations for dummies
#include <string>

int bcc[10][10]={{0,0,0,0,0,0,0,0,0,0},{0,1,2,3,4,5,6,7,8,9},{0,2,4,6,8,10,12,14,16,18},{0,3,6,9,12,15,18,21,24,27},{0,4,8,12,16,20,24,28,32,36},{0,5,10,15,20,25,30,35,40,45},{0,6,12,18,24,30,36,42,48,54},{0,7,14,21,28,35,42,49,56,63},{0,8,16,24,32,40,48,56,64,72},{0,9,18,27,36,45,54,63,72,81}};

std::string strip_0s(std::string n){
    if (n=="0") return n;
    while (n[0]=='0') n.erase(0,1);
    if (n=="") n="0";
    return n;
}

std::string to_str(int n){
    std::string s;
    char c;
    while (n!=0){
        c=(n%10)+48;
        s=c+s;
        n/=10;
    }
    return s;
}

int strcmp(std::string a,std::string b){
    if (a.length()>b.length()) return -1;
    if (b.length()>a.length()) return  1;
    for (int i=0;i<a.length();i++){
        if (a[i]>b[i]) return -1;
        if (a[i]<b[i]) return  1;
    }
    return 0;
}

std::string stradd(std::string a, std::string b){
    std::string c,t;
    char res;
    int i,j,carry=0;
    if (a.length()>b.length()){
        t=a;
        a=b;
        b=t;
    }
    for (i=a.length();i<b.length();i++){
        a='0'+a;
    }
    for (i=a.length()-1;i>=0;i--){
        j=a[i]+b[i]-96+carry;
        carry=j/10;
        res=(j%10)+48;
        c=res+c;
        //cout << j;
    }
    if (carry){
        res=carry+48;
        c=res+c;
    }
    return c;
}

std::string strsub(std::string a, std::string b){
    std::string c,t;
    char res;
    int i,j,carry=0;
    if (strcmp(a,b)==1) return "-"+strsub(b,a); //idk why I would do this but it's an upcoming feature.
    for (i=b.length();i<a.length();i++){
        b='0'+b;
    }
    for (i=a.length()-1;i>=0;i--){
        j=a[i]-b[i]-carry;
        carry=0;
        if (j<0){
            j+=10;
            carry=1;
        }
        res=(j%10)+48;
        c=res+c;
        //cout << j;
    }
    return strip_0s(c);
}

std::string strmulb1d(std::string a, char b){
    std::string c="0",d,zeros;
    int i;
    for (i=a.length()-1;i>=0;i--){
        d=to_str(bcc[a[i]-48][b-48])+zeros;
        c=stradd(c,d);
        zeros+='0';
    }
    return c;
}

std::string strmul(std::string a,std::string b){
    std::string c="0",t,zeros;
    char res;
    int i,j,carry=0;
    for (i=a.length()-1;i>=0;i--){
        t=strmulb1d(b,a[i])+zeros;
        c=stradd(c,t);
        zeros+='0';
    }
    return strip_0s(c);
}

std::string strdivb1d(std::string a,std::string b){
    if (strcmp(a,b)==1) return "0";
    for (int i=1;i<10;i++){
        if (strcmp(a,strmul(b,to_str(i)))==1) return to_str(i-1);
    }
    return "9";
}

std::string strdiv(std::string a,std::string b){
    if (strcmp(a,b)==1) return "0";
    std::string r,d,rem;
    int i,n=a.length();
    for (i=0;i<a.length();i++){
        d=strdivb1d(strip_0s(rem+a[i]),b);
        r+=d;
        rem=strsub(strip_0s(rem+a[i]),strmul(d,b));
        //cout << rem << endl;
    }
    return strip_0s(r);
}

std::string strmod(std::string a,std::string b){
    std::string r,d,rem;
    int i,n=a.length();
    for (i=0;i<a.length();i++){
        d=strdivb1d(strip_0s(rem+a[i]),b);
        r+=d;
        rem=strsub(strip_0s(rem+a[i]),strmul(d,b));
        //cout << rem << endl;
    }
    return strip_0s(rem);
}
