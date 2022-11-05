import sys
sys.setrecursionlimit(100000000)

class PointDatabase:
    class Node:
        def __init__(self,va=None ,p = None ,le=None, rt=None, yl=None):
            self.data = va
            self.left = le
            self.right = rt
            self.pt = p 
            self.ylist = None
            self.ylen = yl

    def __init__(self, pointlist):
        pointlist.sort()
        self.data = pointlist
        self.root = self.build_tree(pointlist, 0, len(pointlist)-1)
        self.add_ylis(self.root)
    def merge_lis(self,P,Q):
        L = [None]*(len(P)+len(Q))
        i,j,t=0,0,0
        while i< len(P) and j<len(Q):
            if P[i][1]<=Q[j][1]:
                L[t]= P[i]
                i+=1
            else :
                L[t]= Q[j]
                j+=1
            t+=1
        if i<len(P):
            while i<len(P):
                L[t]=P[i]
                i+=1
                t+=1
        elif j<len(Q):
            while j<len(Q):
                L[t]=Q[j]
                j+=1
                t+=1
        return L
    

    def give_root(self):
        return self.root

    def build_tree(self, L, s, e):
        if len(L) == 0:
            return None
        if s == e:
            return self.Node(L[s][0],L[s], None, None, 1)

        # else:
        mid = (s+e)//2
        return self.Node(L[mid][0], L[mid],self.build_tree(L, s, mid), self.build_tree(L, mid+1, e), e-s+1)
        # mid+1 is always strictly > (s+e)//2 and <= e  for (length >=2)
    def add_ylis(self,nod):
        if nod.ylen==1:
            nod.ylist = [nod.pt]
        else:
            nod.ylist = self.merge_lis(self.add_ylis(nod.left),self.add_ylis(nod.right))
        return nod.ylist
            

    def binary_search(self, L, low, high):  # all y>= low and y<= high
        lt, rt = 0, len(L)-1
        resl = None
        while lt <= rt:
            mid = (lt+rt)//2
            if L[mid][1] >= low:
                resl = mid
                rt = mid-1
            else:
                lt = mid+1
        lt, rt = 0, len(L)-1
        resr = None
        while lt <= rt:
            mid = (lt+rt)//2
            if L[mid][1] <= high:
                resr = mid
                lt = mid+1
            else:
                rt = mid-1
        return resl, resr

    def update(self, ans, nod, y, d):
        l, r = self.binary_search(nod.ylist, y-d, y+d)
        if l == None or r == None:
            return
        for i in range(l, r+1):
            ans.append(nod.ylist[i])

    def searchNearby(self, q, d):  # x-d and x+d are not presen tin the list
        (x, y) = q
        ptr = self.root
        while ptr != None:
            if ptr.data < x-d:
                ptr = ptr.right
            elif ptr.data > x+d:
                ptr = ptr.left
            else:
                break

        ans = []
        if ptr == None:
            return ans


        trv = ptr.left
        while trv != None:
            if trv.data < x-d:
                trv = trv.right

            else:  # trv.data >=x-d:
                if trv.right == None: # then tree.right == None by construciton
                    self.update(ans, trv, y, d)
                else:
                    self.update(ans, trv.right, y, d)
                trv = trv.left

        trv = ptr.right
        while trv != None:
            if trv.data > x+d:
                trv = trv.left
            else:  # trv.data <=x+d:
                if trv.left == None: # then trv.right == None by construction
                    self.update(ans, trv, y, d)
                else:
                    self.update(ans, trv.left, y, d)
                trv = trv.right
        return ans
