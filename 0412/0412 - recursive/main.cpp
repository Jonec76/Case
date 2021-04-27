#include<fstream>
#include<iostream>
#include<vector>
using namespace std;

void monster(char t, int V, int Z, int G, int p, char* g, int* m, int* v, vector<vector<int> > s)
{
    if(t=='V')
    {
        V--;
    }
    else if(t=='Z')
    {
        Z--;
    }
    else
    {
        G--;
    }
    g[p-1]=t;
    int array_size=s.size();
    int grid_size=(array_size/4)*(array_size/4);
    int* cal_m= new int[array_size];
    //cout<<array_size<<grid_size;
    for(int i=0;i<array_size;i++)
    {
        cal_m[i]=0;
    }
    for(int i=0;i<grid_size;i++)
    {
        if(g[i]=='V')
        {
            for(int j=0;j<array_size;j++)
            {
                for(int k=0;k<s[j].size();k++)
                {
                    if(abs(s[j][k])==i+1 && s[j][k]>0)
                    {
                        cal_m[j]=cal_m[j]+1;
                    }
                }
            }
        }
        if(g[i]=='Z')
        {
            for(int j=0;j<array_size;j++)
            {
                for(int k=0;k<s[j].size();k++)
                {
                    if(abs(s[j][k])==i+1)
                    {
                        cal_m[j]=cal_m[j]+1;
                    }
                }
            }
        }
        if(g[i]=='G')
        {
            for(int j=0;j<array_size;j++)
            {
                for(int k=0;k<s[j].size();k++)
                {
                    if(abs(s[j][k])==i+1 && s[j][k]<0)
                    {
                        cal_m[j]=cal_m[j]+1;
                    }
                }
            }
        }
    }
    /*for(int i=0;i<array_size;i++)
    {
        cout<<cal_m[i]<<endl;
    }
    cout<<"---------------------------------"<<endl;
    for(int i=0;i<grid_size;i++)
    {
        cout<<g[i]<<endl;
    }
    cout<<"---------------------------------"<<endl;*/
    int stop=0,ans=0;
    for(int i=0;i<array_size;i++)
    {
        //cout<<cal_m[i]<<" "<<v[i]<<endl;
        if(cal_m[i]>v[i])
        {
            stop=1;
            break;
        }
        if(cal_m[i]==v[i])
        {
            ans=ans+1;
        }
    }
    int Mcount=0;
    Mcount=V+Z+G;
    if (stop==1)
    {
        //cout<<"STOP!!!"<<endl;
    }
    if(stop==0)
    {
        if(Mcount==0)
        {
            /*for(int i=0;i<array_size;i++)
            {
                cout<<cal_m[i]<<endl;
            }
            cout<<"---------------------------------"<<endl;*/
            if(ans==array_size)
            {
                for(int i=0;i<grid_size;i++)
                {
                    cout<<g[i];
                    if((i+1)%(array_size/4)==0 && i+1>1)
                    {
                        cout<<endl;
                    }
                }
            cout<<"-----------------------------------"<<endl;
            }
        }
        else
        {
            for(int k=0;k<grid_size;k++)
            {
                if(m[k]==0 && k+1>p)
                {
                    char *ng = new char[grid_size];
                    for(int l=0;l<grid_size;l++)
                    {
                        ng[l]=g[l];
                    }
                    if(V>0)
                    {
                        monster('V',V,Z,G,k+1,ng,m,v,s);
                    }
                    for(int l=0;l<grid_size;l++)
                    {
                        ng[l]=g[l];
                    }
                    if(Z>0)
                    {
                        monster('Z',V,Z,G,k+1,ng,m,v,s);
                    }
                    for(int l=0;l<grid_size;l++)
                    {
                        ng[l]=g[l];
                    }
                    if(G>0)
                    {
                        monster('G',V,Z,G,k+1,ng,m,v,s);
                    }

                    break;
                }
            }
        }
    }

}
int change_direct(int direct,int step,int m,int M)
{
    int d;
    if(m==1)
    {
        if(direct==1)
        {
            d=4;
        }
        else if(direct==2)
        {
            d=3;
        }
        else if(direct==3)
        {
            d=2;
        }
        else
        {
            d=1;
        }
    }
    else
    {
        if(direct==1)
        {
            d=3;
        }
        else if(direct==2)
        {
            d=4;
        }
        else if(direct==3)
        {
            d=1;
        }
        else
        {
            d=2;
        }
    }
    return d;
}
int change_step(int direct,int M)
{
    int step;
    if(direct==1)
    {
        step=M;
    }
    else if(direct==2)
    {
        step=-M;
    }
    else if(direct==3)
    {
        step=1;
    }
    else
    {
        step=-1;
    }

    return step;
}
int main()
{
    ifstream ifs;
    ifs.open("input.txt");
    int Vcount,Zcount,Gcount,Msize;

    ifs>> Vcount>>Zcount>>Gcount;
    ifs>>Msize;
    int *vis = new int[Msize*4];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<Msize;j++)
        {
            ifs>>vis[Msize*i+j];
        }
    }
    char *grid = new char[Msize*Msize];
    int *mirror = new int[Msize*Msize];
    for(int i=0;i<Msize;i++)
    {
        for(int j=0;j<Msize;j++)
        {
            ifs>>grid[Msize*i+j];
            if(grid[Msize*i+j]=='.')
            {
                mirror[Msize*i+j]=0;
            }
            else if(grid[Msize*i+j]=='/')
            {
                mirror[Msize*i+j]=1;
            }
            else
            {
                mirror[Msize*i+j]=2;
            }
        }
    }
    vector<vector<int> > see;
    int pos,start,sstep,sstart,stime,Tm;
    int direct;
    int step;
    for(int k=0;k<4*Msize;k++)
    {
        Tm=1;
        if (k==0 || k==Msize || k==Msize*2 ||k==Msize*3)
        {
            stime=0;
        }
        vector<int> a;
        see.push_back(a);
        if(k<Msize)
        {
            sstart=1;
            sstep=1;
            start=sstart+sstep*stime;
            stime++;
            direct=1;
            step=Msize;
            pos=start;
        }
        else if(k>=Msize && k<2*Msize)
        {
            sstart=Msize*(Msize-1)+1;
            sstep=1;
            start=sstart+sstep*stime;
            stime++;
            direct=2;//1�U2�W3�k4��
            step=-Msize;
            pos=start;
        }
        else if(k>=2*Msize && k<3*Msize)
        {
            sstart=1;
            sstep=Msize;
            start=sstart+sstep*stime;
            stime++;
            direct=3;//1�U2�W3�k4��
            step=1;
            pos=start;
        }
        else
        {
            sstart=Msize;
            sstep=Msize;
            start=sstart+sstep*stime;
            stime++;
            direct=4;//1�U2�W3�k4��
            step=-1;
            pos=start;
        }
        while(pos<=Msize*Msize && pos>=1)
        {
            if (mirror[pos-1]==0)
            {
                see[k].push_back(pos*Tm);
                if(step==1)
                {
                    if(pos%Msize==0){
                        break;
                    }
                }
                if(step==-1)
                {
                    if(pos%Msize==1)
                    {
                        break;
                    }
                }
                pos=pos+step;
            }
            else if (mirror[pos-1]==1)
            {
                int dir=direct;
                direct=change_direct(dir, step, mirror[pos-1],Msize);
                step=change_step(direct,Msize);
                Tm=-1;
                if(step==1)
                {
                    if(pos%Msize==0){
                        break;
                    }
                }
                if(step==-1)
                {
                    if(pos%Msize==1)
                    {
                        break;
                    }
                }
                pos=pos+step;
            }
            else
            {
                int dir=direct;
                direct=change_direct(dir, step, mirror[pos-1],Msize);
                step=change_step(direct,Msize);
                Tm=-1;
                if(step==1)
                {
                    if(pos%Msize==0){
                        break;
                    }
                }
                if(step==-1)
                {
                    if(pos%Msize==1)
                    {
                        break;
                    }
                }
                pos=pos+step;
            }
        }
    }
    for(int k=0;k<Msize*Msize;k++)
    {
        if(mirror[k]==0)
        {
            if(Vcount+Zcount+Gcount!=0)
            {
                if(Vcount!=0)
                {
                    monster('V',Vcount,Zcount,Gcount,k+1,grid,mirror,vis,see);
                }
                if(Zcount!=0)
                {
                    monster('Z',Vcount,Zcount,Gcount,k+1,grid,mirror,vis,see);
                }
                if(Gcount!=0)
                {
                    monster('G',Vcount,Zcount,Gcount,k+1,grid,mirror,vis,see);
                }
            }
            break;
        }
    }
}
