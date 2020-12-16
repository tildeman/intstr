//Integer (unsigned) string operations for dummies
#include <string>
typedef std::string _cxxstr;

//Pre-built multiplication table
int bcc[10][10]={{0,0,0,0,0,0,0,0,0,0},{0,1,2,3,4,5,6,7,8,9},{0,2,4,6,8,10,12,14,16,18},{0,3,6,9,12,15,18,21,24,27},{0,4,8,12,16,20,24,28,32,36},{0,5,10,15,20,25,30,35,40,45},{0,6,12,18,24,30,36,42,48,54},{0,7,14,21,28,35,42,49,56,63},{0,8,16,24,32,40,48,56,64,72},{0,9,18,27,36,45,54,63,72,81}};

// Utility functions

_cxxstr to_str(int n){
    _cxxstr s;
    char c;
    if (n<0) return "-"+to_str(-n);
    if (n==0) return "0";
    while (n!=0){
        c=(n%10)+48;
        s=c+s;
        n/=10;
    }
    return s;
}

_cxxstr reduce_sign(_cxxstr n){
    int s=0,i;
    for (i=0;i<n.length();i++){
        if (n[i]=='+') s+=0;
        else if (n[i]=='-') s=(s+1)%2;
        else break;
    }
    while (n[0]=='+' or n[0]=='-') n.erase(0,1);
    if (n=="0") return "0";
    if (s==1) n='-'+n;
    return n;
}

_cxxstr strip_0s_u(_cxxstr n){
    n+='a';
    while (n[0]=='0') n.erase(0,1);
    if (n=="a") n="0";
    else n.erase(n.length()-1,1);
    return n;
}

int sign_check(_cxxstr n){
    n=reduce_sign(n);
    if (n[0]=='-') return -1;
    n=strip_0s_u(n);
    if (n=="0") return 0;
    return 1;
}

_cxxstr strip_0s(_cxxstr n){
    n=reduce_sign(n);
    if (sign_check(n)==-1){
        n.erase(0,1);
        n=strip_0s_u(n);
        return '-'+n;
    }
    else if (sign_check(n)==0) return "0";
    else if (sign_check(n)==1){
        n=strip_0s_u(n);
        return n;
    }
    return "0";
}

// Unsigned functions

int strcmpr_u(_cxxstr a,_cxxstr b){
    a=strip_0s_u(a);
    b=strip_0s_u(b);
    if (a.length()>b.length()) return -1;
    if (b.length()>a.length()) return  1;
    for (int i=0;i<a.length();i++){
        if (a[i]>b[i]) return -1;
        if (a[i]<b[i]) return  1;
    }
    return 0;
}

int strcmpr(_cxxstr a,_cxxstr b){
    a=reduce_sign(a);
    b=reduce_sign(b);
    if (sign_check(a)>=0 and sign_check(b)>=0) return strcmpr_u(a,b);
    else if (sign_check(a)>=0 and sign_check(b)<0) return -1;
    else if (sign_check(a)<0 and sign_check(b)>=0) return 1;
    else if (sign_check(a)>=0 and sign_check(b)>=0){
        a.erase(0,1);
        b.erase(0,1);
        return strcmpr(b,a);
    }
    return 0;
}

_cxxstr stradd_u(_cxxstr a, _cxxstr b){
    _cxxstr c,t;
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
    }
    if (carry){
        res=carry+48;
        c=res+c;
    }
    return c;
}

_cxxstr strsub_u(_cxxstr a, _cxxstr b){
    _cxxstr c,t;
    char res;
    int i,j,carry=0;
    if (strcmpr_u(a,b)==1) return '-'+strsub_u(b,a);
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
    }
    return strip_0s(c);
}

_cxxstr strmulb1d(_cxxstr a, char b){
    _cxxstr c="0",d,zeros;
    int i;
    for (i=a.length()-1;i>=0;i--){
        d=to_str(bcc[a[i]-48][b-48])+zeros;
        c=stradd_u(c,d);
        zeros+='0';
    }
    return c;
}

_cxxstr strmul_u(_cxxstr a,_cxxstr b){
    _cxxstr c="0",t,zeros;
    char res;
    int i,j,carry=0;
    for (i=a.length()-1;i>=0;i--){
        t=strmulb1d(b,a[i])+zeros;
        c=stradd_u(c,t);
        zeros+='0';
    }
    return strip_0s(c);
}

_cxxstr strdivb1d(_cxxstr a,_cxxstr b){
    if (strcmpr_u(a,b)==1) return "0";
    for (int i=1;i<10;i++){
        if (strcmpr_u(a,strmul_u(b,to_str(i)))==1) return to_str(i-1);
    }
    return "9";
}

_cxxstr strdiv_u(_cxxstr a,_cxxstr b){
    if (strcmpr_u(a,b)==1) return "0";
    _cxxstr r,d,rem;
    int i,n=a.length();
    for (i=0;i<a.length();i++){
        d=strdivb1d(strip_0s(rem+a[i]),b);
        r+=d;
        rem=strsub_u(strip_0s(rem+a[i]),strmul_u(d,b));
    }
    return strip_0s_u(r);
}

_cxxstr strmod_u(_cxxstr a,_cxxstr b){
    _cxxstr r,d,rem;
    int i,n=a.length();
    for (i=0;i<a.length();i++){
        d=strdivb1d(strip_0s_u(rem+a[i]),b);
        r+=d;
        rem=strsub_u(strip_0s_u(rem+a[i]),strmul_u(d,b));
    }
    return strip_0s_u(rem);
}

// Signed functions

_cxxstr stradd(_cxxstr a, _cxxstr b){
    a=strip_0s(reduce_sign(a));
    b=strip_0s(reduce_sign(b));
    int aa=sign_check(a), bb=sign_check(b);
    if (aa>=0 and bb>=0) return stradd_u(a,b);
    else if (aa<0 and bb>=0){
        a.erase(0,1);
        return strsub_u(b,a);
    }
    else if (aa>=0 and bb<0){
        b.erase(0,1);
        return strsub_u(a,b);
    }
    else if (aa<0 and bb<0){
        a.erase(0,1);
        b.erase(0,1);
        return '-'+stradd_u(a,b);
    }
    return "0";
}

_cxxstr strsub(_cxxstr a, _cxxstr b){
    a=strip_0s(reduce_sign(a));
    b=strip_0s(reduce_sign(b));
    int aa=sign_check(a), bb=sign_check(b);
    if (aa>=0 and bb>=0) return strsub_u(a,b);
    else if (aa<0 and bb>=0){
        a.erase(0,1);
        return '-'+stradd_u(b,a);
    }
    else if (aa>=0 and bb<0){
        b.erase(0,1);
        return stradd_u(a,b);
    }
    else if (aa<0 and bb<0){
        a.erase(0,1);
        b.erase(0,1);
        return strsub_u(b,a);
    }
    return "0";
}

_cxxstr strmul(_cxxstr a,_cxxstr b){
    a=strip_0s(reduce_sign(a));
    b=strip_0s(reduce_sign(b));
    int aa=sign_check(a),bb=sign_check(b);
    if (aa>=0 and bb>=0) return strmul_u(a,b);
    else if (aa>=0 and bb<0){
        b.erase(0,1);
        return '-'+strmul_u(a,b);
    }
    else if (aa<0 and bb>=0){
        a.erase(0,1);
        return '-'+strmul_u(a,b);
    }
    else if (aa<0 and bb<0){
        a.erase(0,1);
        b.erase(0,1);
        return strmul_u(a,b);
    }
    return "0";
}

_cxxstr strdiv(_cxxstr a,_cxxstr b){
    a=strip_0s(reduce_sign(a));
    b=strip_0s(reduce_sign(b));
    int aa=sign_check(a),bb=sign_check(b);
    if (aa>=0 and bb>=0) return strdiv_u(a,b);
    else if (aa>=0 and bb<0){
        b.erase(0,1);
        return '-'+strdiv_u(a,b);
    }
    else if (aa<0 and bb>=0){
        a.erase(0,1);
        return '-'+strdiv_u(a,b);
    }
    else if (aa<0 and bb<0){
        a.erase(0,1);
        b.erase(0,1);
        return strdiv_u(a,b);
    }
    return "0";
}

_cxxstr strmod(_cxxstr a,std::string b){
    a=strip_0s(reduce_sign(a));
    b=strip_0s(reduce_sign(b));
    int aa=sign_check(a),bb=sign_check(b);
    if (bb>=0){
        if (aa>=0) return strmod_u(a,b);
        else if (aa<0){
            a.erase(0,1);
            return strsub(b,strmod_u(a,b));
        }
    }
    else if (bb<0){
        if (aa>=0) {
            b.erase(0,1);
            return stradd(strsub("0",b),strmod_u(a,b));
        }
        else if (aa<0){
            a.erase(0,1);
            b.erase(0,1);
            return strsub("0",strmod_u(a,b));
        }
    }
    return "0";
}