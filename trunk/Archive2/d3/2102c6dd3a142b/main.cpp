#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
bool interval(int a1,int b1,int a2,int b2){
    if(b1<=a2)return false;
	if(a1>=b2)return false;
	return true;
}
bool in_interval(int a,int b,int x){
	return x>a&&x<b;
}
struct Point{
	int x,y;
	Point(int a,int b){x=a;y=b;}
};
struct Rect{
	int tx,ty,bx,by;
	bool intersect(const Rect& other)const{
		return interval(tx,bx,other.tx,other.bx)&&
			   interval(ty,by,other.ty,other.by);
	}
};
bool compare_rect(const Rect *a,const Rect *other){
	if(a->tx!=other->tx)return a->tx<other->tx;
	if(a->ty!=other->ty)return a->ty<other->ty;
	if(a->bx!=other->bx)return a->bx<other->bx;
	if(a->by!=other->by)return a->by<other->by;
	return false;
}
int main(){
	int M;
	scanf("%d",&M);
	Rect rect[M];
	vector<Rect*> merged;
	merged.push_back(rect);
	//finds the hull of the perimeter
	for(int i=0;i<M;++i){
		int tx,ty,bx,by;
		scanf("%d %d %d %d",&tx,&ty,&bx,&by);
		rect[i].tx=tx;
		rect[i].ty=ty;
		rect[i].bx=bx;
		rect[i].by=by;
		for(int j=0;j<merged.size();++j){
			if(rect[i].intersect(*merged[j])){
				merged.push_back(&rect[i]);
				printf("%d intersects %ld\n",i,merged[j]-rect);
				break;
			}
		}
	}
	sort(merged.begin(),merged.end(),compare_rect);
	int cur_rect=0,dir=0;
	Point cur_pos(merged[cur_rect]->tx,merged[cur_rect]->ty);
	bool first=true;
	Point initial(merged[cur_rect]->tx,merged[cur_rect]->ty);
	unsigned int perimeter=0;
	while(1){
		if(!first&&cur_pos.x==initial.x&&cur_pos.y==initial.y){
			break;
		}
		first=false;
		bool collided=false;
		printf("%d %d %d %d\n",cur_rect,dir,cur_pos.x,cur_pos.y);
		for(int i=0;i<merged.size();++i){
			if(cur_rect!=i){
				if(dir==0){
					if(in_interval(merged[i]->ty,merged[i]->by,cur_pos.y)&&
					   in_interval(cur_pos.x,merged[cur_rect]->bx,merged[i]->tx)){
						   cur_pos.x=merged[i]->tx;
						   cur_pos.y=cur_pos.y;
						   cur_rect=i;
						   dir=3;
						   printf("collided\n");
						   perimeter+=merged[i]->tx-cur_pos.x;
						   collided=true;
						   break;
					}
				}else if(dir==1){
					if(in_interval(merged[i]->tx,merged[i]->bx,cur_pos.x)&&
					   in_interval(cur_pos.y,merged[cur_rect]->by,merged[i]->ty)){
						   cur_pos.x=cur_pos.x;
						   cur_pos.y=merged[i]->ty;
						   cur_rect=i;
						   dir=0;
						   printf("collided\n");
						   perimeter+=merged[i]->ty-cur_pos.y;
						   collided=true;
						   break;
					}
				}else if(dir==2){
					if(in_interval(merged[i]->ty,merged[i]->by,cur_pos.y)&&
					   in_interval(merged[cur_rect]->tx,cur_pos.x,merged[i]->bx)){
						   cur_pos.x=merged[i]->bx;
						   cur_pos.y=cur_pos.y;
						   cur_rect=i;
						   dir=1;
						   printf("collided\n");
						   perimeter+=cur_pos.x+merged[i]->bx;
						   collided=true;
						   break;
					}
				}else if(dir==3){
					if(in_interval(merged[i]->tx,merged[i]->bx,cur_pos.x)&&
					   in_interval(merged[cur_rect]->ty,cur_pos.y,merged[i]->by)){
						   cur_pos.x=cur_pos.x;
						   cur_pos.y=merged[i]->by;
						   cur_rect=i;
						   dir=2;
						   printf("collided\n");
						   perimeter+=cur_pos.y-merged[i]->by;
						   collided=true;
						   break;
					}
				}
			}
		}
		if(!collided){
			printf("passed\n");
			if(dir==0){
				perimeter+=merged[cur_rect]->tx-cur_pos.x;
				cur_pos.x=merged[cur_rect]->bx;
				cur_pos.y=merged[cur_rect]->ty;
				dir=1;
			}else if(dir==1){
				perimeter+=merged[cur_rect]->ty-cur_pos.y;
				cur_pos.x=merged[cur_rect]->bx;
				cur_pos.y=merged[cur_rect]->by;
				dir=2;
			}else if(dir==2){
				perimeter+=cur_pos.x-merged[cur_rect]->bx;
				cur_pos.x=merged[cur_rect]->tx;
				cur_pos.y=merged[cur_rect]->by;
				dir=3;
			}else if(dir==3){
				perimeter+=cur_pos.y-merged[cur_rect]->by;
				cur_pos.x=merged[cur_rect]->tx;
				cur_pos.y=merged[cur_rect]->ty;
				dir=0;
			}
		}
	}
	printf("%d\n",perimeter);
	return 0;
}
