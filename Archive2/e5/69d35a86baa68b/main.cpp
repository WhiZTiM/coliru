List List::operator +(List& list){
     List retList(list.size() + arrSize);
     for(int x=0;x<arrSize;x++){
         retList[x]=array[x];
     }
     for(int x=arrSize;x<list.size()+arrSize;x++){
         retList[x]=list[x];
     }
     return retList;
 }
