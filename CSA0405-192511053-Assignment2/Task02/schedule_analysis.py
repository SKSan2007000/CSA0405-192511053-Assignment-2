jobs=[('P1',0,8,2),('P2',1,4,1),('P3',2,9,3),('P4',3,5,2)]
def show(title,segments,finish,first):
 print('\n'+title+' Gantt: '+' '.join(f'{p}({a}-{b})' for p,a,b in segments)); sw=st=sr=0
 for p,a,b,pr in jobs:
  tat=finish[p]-a; wt=tat-b; rt=first[p]-a; sw+=wt;st+=tat;sr+=rt;print(f'{p}: CT={finish[p]} TAT={tat} WT={wt} RT={rt}')
 print(f'Average TAT={st/4:.2f} WT={sw/4:.2f} RT={sr/4:.2f}')
# FCFS
seg=[];f={};first={};t=0
for p,a,b,pr in jobs:
 t=max(t,a);first[p]=t;seg.append((p,t,t+b));t+=b;f[p]=t
show('FCFS',seg,f,first)
# Non-preemptive SJF
seg=[];f={};first={};left=jobs[:];t=0
while left:
 ready=[x for x in left if x[1]<=t]
 if not ready:t=min(x[1] for x in left);ready=[x for x in left if x[1]<=t]
 x=min(ready,key=lambda z:z[2]);p,a,b,pr=x;first[p]=t;seg.append((p,t,t+b));t+=b;f[p]=t;left.remove(x)
show('SJF',seg,f,first)
# SRTF, one-unit segments coalesced
rem={p:b for p,a,b,pr in jobs};f={};first={};seg=[];t=0;last=None;start=0
while len(f)<4:
 ready=[x for x in jobs if x[1]<=t and rem[x[0]]>0]
 if not ready:t+=1;continue
 x=min(ready,key=lambda z:rem[z[0]]);p=x[0]
 if p not in first:first[p]=t
 if last!=p:
  if last is not None:seg.append((last,start,t))
  last=p;start=t
 rem[p]-=1;t+=1
 if rem[p]==0:f[p]=t
if last is not None:seg.append((last,start,t))
show('SRTF',seg,f,first)
# Non-preemptive priority, lower number is higher priority
seg=[];f={};first={};left=jobs[:];t=0
while left:
 ready=[x for x in left if x[1]<=t]
 if not ready:t=min(x[1] for x in left);ready=[x for x in left if x[1]<=t]
 x=min(ready,key=lambda z:(z[3],z[1]));p,a,b,pr=x;first[p]=t;seg.append((p,t,t+b));t+=b;f[p]=t;left.remove(x)
show('Priority',seg,f,first)
