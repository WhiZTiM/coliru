for(int i=0;i<tris.size();i++)
{
    Point3D p1(tris[i].x1,tris[i].y1,tris[i].z1);
    Point3D p2(tris[i].x2,tris[i].y2,tris[i].z2);
    Point3D p3(tris[i].x3,tris[i].y3,tris[i].z3);
    
    for(int j=0;j<tris.size();j++){
        Point3D q1(tris[j].x1,tris[j].y1,tris[j].z1);
        Point3D q2(tris[j].x2,tris[j].y2,tris[j].z2);
        Point3D q3(tris[j].x3,tris[j].y3,tris[j].z3);
        
        int counter=0;
        if(((p1.x==q1->x)&&(p1.y==q1->y) // change these also &&(p1->z==q1->z))||((p1->x==q2->x)&&(p1->y==q2->y)&&(p1->z==q2->z))||((p1->x==q3->x)&&(p1->y==q3->y)&&(p1->z==q3->z))) counter++;
        if(((p2.x==q1->x)&&(p2.y==q1->y) // change these also &&(p2->z==q1->z))||((p2->x==q2->x)&&(p2->y==q2->y)&&(p2->z==q2->z))||((p2->x==q3->x)&&(p2->y==q3->y)&&(p2->z==q3->z))) counter++;
        if(((p3.x==q1->x)&&(p3.y==q1->y) // change these also &&(p3->z==q1->z))||((p3->x==q2->x)&&(p3->y==q2->y)&&(p3->z==q2->z))||((p3->x==q3->x)&&(p3->y==q3->y)&&(p3->z==q3->z))) counter++;
        if(counter==2){
            LineSeg3D graphline(centroids[i].x,centroids[i].y,centroids[i].z,
                centroids[j].x,centroids[j].y,centroids[j].z,Colour::white);
            dualgraph.resize(dualgraph.size()+1);
            dualgraph.push_back(graphline);
            paths[i][j]=1;
        }
    }
}