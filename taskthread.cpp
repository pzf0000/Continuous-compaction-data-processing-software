#include "taskthread.h"

void taskthread::run()
{
	Datavec->clear();
	void (*f)(int,int,void *t);
	f = callback;
	ifstream input(filename);
	findcol(input);
	readcsv(input,f,(void *)this,*Datavec);
	input.close();

	updateinfo2(Datavec->size());
    //不再处理错误数据了
    /*double speedsum = 0,rmvsum = 0,cmvsum = 0,hzsum = 0;
	for(Data &data:*Datavec)
		speedsum += data.GetSpeed(),rmvsum += data.GetRMV(),cmvsum == data.GetCMV(),hzsum = data.GetHz();
	size_t Size = (*Datavec).size();
	speedsum /= Size,rmvsum /= Size,cmvsum /= Size,hzsum /= Size;
	double sdtmp = 0,rmvtmp = 0,cmvtmp = 0,hztmp = 0;
	for(Data &data:*Datavec)
		sdtmp += (data.GetSpeed()-speedsum)*(data.GetSpeed()-speedsum),
		         rmvtmp += (data.GetRMV()-rmvsum)*(data.GetRMV()-rmvsum),
		                   cmvtmp += (data.GetCMV()-cmvsum)*(data.GetCMV()-cmvsum),
		                             hztmp += (data.GetHz()-hzsum)*(data.GetHz()-hzsum);
	double sd = sqrt(sdtmp/Size),rmvsd = sqrt(rmvtmp/Size),cmvsd = sqrt(cmvtmp/Size),hzsd = sqrt(hztmp/Size);
	for(auto it = (*Datavec).begin() ; it != (*Datavec).end() ;)
		if(fabs(it->GetSpeed()-speedsum)>3*sd||fabs(it->GetRMV()-rmvsum)>3*rmvsd||fabs(it->GetCMV()-cmvsum)>3*cmvsd||fabs(it->GetHz()-hzsum)>3*hzsd)
			it = Datavec->erase(it);
		else it++;
    updateinfo2(Datavec->size());*/
	double Max = -0x3f3f3f3f,Min = 0x3f3f3f3f;
	double Max2 = -0x3f3f3f3f,Min2 = 0x3f3f3f3f;

	for(Data &data:*Datavec)
	{
		Max = max(Max,data.Ry);
		Max = max(Max,data.Ly);
		Min = min(Min,data.Ry);
		Min = min(Min,data.Ly);
		Max2 = max(Max2,data.Rx);
		Max2 = max(Max2,data.Lx);
		Min2 = min(Min2,data.Rx);
		Min2 = min(Min2,data.Lx);
	}

	*a = Max2,*b = Min2,*c = Max,*d = Min;

	paintChart(Datavec);
}
