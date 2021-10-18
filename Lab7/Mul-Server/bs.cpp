int i,n,d, t;
cin>>t;
for(int i=0; i<t; i++)
{
    cin>>n>>d;
    int a[n];
    for(j=0;j<n;j++)
        cin>>a[j];
    leftRotate(a,d,n);
    printArray(a,n);
}