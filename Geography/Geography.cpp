#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
using namespace std;
using ll = long long ;
using P = pair<int,int> ;
using pll = pair<long long,long long>;
constexpr int INF = 1e9;
constexpr long long LINF = 1e17;
constexpr int MOD = 1000000007;
constexpr double PI = 3.14159265358979323846;

using d = double;
constexpr double EPS = 1e-10;
constexpr bool eq(const d& x,const d& y){return abs(x-y)<EPS;}
struct point{
    d x=0,y=0;
    constexpr point(const d& x=0,const d& y=0):x(x),y(y){}
    constexpr bool operator==(const point& r)const{return eq(x,r.x)&&eq(y,r.y);};
    constexpr bool operator!=(const point& r)const{return !(*this==r);};
    constexpr bool operator<(const point& r)const{return (eq(x,r.x))?(y<r.y):(x<r.x);};
    constexpr bool operator>(const point& r)const{return (eq(x,r.x))?(y>r.y):(x>r.x);};
    constexpr point operator+(const point& r)const{return point(*this)+=r;}
    constexpr point operator+=(const point& r){
        x+=r.x;y+=r.y;
        return *this;
    }
    constexpr point operator-(const point& r)const{return point(*this)-=r;}
    constexpr point operator-=(const point& r){
        x-=r.x;y-=r.y;
        return *this;
    }
    constexpr point operator*(const d& r)const{return point(*this)*=r;}
    constexpr point operator*=(const d& r){
        x*=r;y*=r;
        return *this;
    }
    constexpr point operator*(const point& r)const{return point(*this)*=r;}
    constexpr point operator*=(const point& r){
        d tmp=x;
        x=x*r.x-y*r.y;
        y=tmp*r.y+y*r.x;
        return *this;
    }
    constexpr point operator/(const double& r)const{return point(*this)/=r;}
    constexpr point operator/=(const double& r){
        x/=r;y/=r;
        return *this;
    }
};
d norm(const point& a){return a.x*a.x+a.y*a.y;}
double abs(const point& a){return sqrt(a.x*a.x+a.y*a.y);}
d dot(const point& a,const point& b){return a.x*b.x+a.y*b.y;}
d cross(const point& a,const point& b){return a.x*b.y-a.y*b.x;}
point projection(const point& p,const point& b){return b*dot(p,b)/norm(b);}
point unit_vec(const point& p){return p/abs(p);}
point normal_vec(const point& p){return p*point(0,1);}
point rotation(const point& center,const point& p,const point& rot){return rot*(p-center)+center;}
double area(const point& a,const point& b,const point& c){return cross(b-a,c-a)/2;}

struct Line{
    point a,b;
    constexpr Line(const point& a=point(0,0),const point& b=point(0,0)):a(a),b(b){}
    constexpr Line(const double& A,const double& B,const double& C){ // Ax + By + C = 0
        if(eq(A,0)&&eq(B,0)) assert(-1);
        else if(eq(B,0)){
            a = point(-C/A,0);
            b = point(-C/A,1);
        }else{
            a = point(0,-C/B);
            b = point(1,-(A+C)/B);
        }
    }
};
bool is_orthoonal(const Line& l,const Line& r){return eq(dot(l.b-l.a,r.b-r.a),0);}
bool is_pararell(const Line& l,const Line& r){return eq(cross(l.b-l.a,r.b-r.a),0);}
bool on_Line(const Line& l,const point& p){return eq(dot(p-l.a,l.b-l.a),0);}
double dis_Lp(const Line& l,const point& p){return abs(cross(l.b-l.a,p-l.a))/abs(l.b-l.a);}
point Line_intersect(const Line& l,const Line& r){
    point lv=l.b-l.a,rv=r.b-r.a;
    return l.a + lv * abs(cross(r.b-l.a,rv) / cross(lv,rv)); 
}
Line vertical_bisector(const point& p,const point& q){return Line((p+q)/2,rotation((p+q)/2,q,point(0,1)));}
using Segment = Line;
bool on_Segment(const Segment& s,const point& p){
    return ( abs(s.a-p)+abs(s.b-p)<abs(s.a-s.b)+EPS );
}
bool is_segment_intersect(const Segment& s,const Segment& t){
    return  (cross(s.b-s.a,t.a-s.a) * cross(s.b-s.a,t.b-s.a) < EPS) &&
            (cross(t.b-t.a,s.a-t.a) * cross(t.b-t.a,s.b-t.a) < EPS);
}
point segment_intersect(const Segment& s,const Segment& t){
    double d1 = dis_Lp(s,t.a);
    double d2 = dis_Lp(s,t.b); 
    double p = d1/(d1+d2);
    return t.a + (t.b-t.a)*p;
}

bool on_circle(point cen,point p){
    return (cen.x-p.x)*(cen.x-p.x)+(cen.y-p.y)*(cen.y-p.y)<=1+EPS;
}

int main(){
    int n;
    while(cin >> n){
        if(n==0) break;
        vector<point> points(n);
        rep(i,n) cin >> points[i].x >> points[i].y;
        vector<point> centers;
        vector<Line> lines;
        rep(i,n)rep(j,i) centers.push_back((points[i]+points[j])/2);
        rep(i,n)rep(j,i) lines.push_back(vertical_bisector(points[i],points[j]));
        rep(i,n)rep(j,i){
            if(is_pararell(lines[i],lines[j])) continue;
            centers.push_back(Line_intersect(lines[i],lines[j]));
        }

        int mx = 1;
        for(point c:centers){
            int res = 0;
            rep(i,n){
                if(on_circle(c,points[i])) ++res;
            }
            mx = max(res,mx);
        }
        cout << mx << endl;
    }
    return 0;
}