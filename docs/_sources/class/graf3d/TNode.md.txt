<!-- TNode.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 1月 13 16:05:45 2018 (+0800)
;; Last-Updated: 三 9月 16 10:44:38 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TNode*

继承 public TNamed , public TAttLine, public TAttFill, public TAtt3D

## class


```cpp
public:
   TNode();

/// Node normal constructor.
///  - name        is the name of the node
///  - title       is title
///  - shapename   is the name of the referenced shape
///  - x,y,z       are the offsets of the volume with respect to his mother
///  - matrixname  is the name of the rotation matrix
///    This new node is added into the list of sons of the current node
   TNode(const char *name, const char *title, const char *shapename, Double_t x=0, Double_t y=0, Double_t z=0,
         const char *matrixname="", Option_t *option="");

/// Node normal constructor.
///  - name    is the name of the node
///  - title   is title
///  - shape   is the pointer to the shape definition
///  - x,y,z   are the offsets of the volume with respect to his mother
///  - matrix  is the pointer to the rotation matrix
///    This new node is added into the list of sons of the current node
   TNode(const char *name, const char *title, TShape *shape, Double_t x=0, Double_t y=0, Double_t z=0,
         TRotMatrix *matrix=0, Option_t *option="");
   virtual ~TNode();
   virtual void        Browse(TBrowser *b);/// Browse.

/// Create the list to support sons of this node.
   virtual void        BuildListOfNodes();

/// Change Current Reference node to this.
   virtual void        cd(const char *path=0); // *MENU*

/// Compute distance from point px,py to a Node.
///  Compute the closest distance of approach from point px,py to this node.
///  The distance is computed in pixels units.
   virtual Int_t       DistancetoPrimitive(Int_t px, Int_t py);

/// Draw Referenced node with current parameters.
   virtual void        Draw(Option_t *option=""); // *MENU*

/// Draw only Sons of this node.
   virtual void        DrawOnly(Option_t *option="");

/// Execute action corresponding to one event.
///  This member function must be implemented to realize the action
///  corresponding to the mouse click on the object in the window
   virtual void        ExecuteEvent(Int_t event, Int_t px, Int_t py);
   TList              *GetListOfNodes() const {return fNodes;}
   virtual TRotMatrix *GetMatrix() const {return fMatrix;}

/// Return pointer to node with name in the node tree.
   virtual TNode      *GetNode(const char *name) const;

/// Get object info.
   virtual char       *GetObjectInfo(Int_t px, Int_t py) const;
   const   Option_t   *GetOption() const { return fOption.Data();}
   virtual TNode      *GetParent() const {return fParent;}
   TShape             *GetShape() const {return fShape;}
   Int_t               GetVisibility() const {return fVisibility;}
   virtual Double_t    GetX() const {return fX;}
   virtual Double_t    GetY() const {return fY;}
   virtual Double_t    GetZ() const {return fZ;}

/// Copy shape attributes as node attributes.
   virtual void        ImportShapeAttributes();

/// Return TRUE if node contains nodes, FALSE otherwise.
   Bool_t              IsFolder() const;

/// Convert one point from local system to master reference system.
///  Note that before invoking this function, the global rotation matrix
///  and translation vector for this node must have been computed.
///  This is automatically done by the Paint functions.
///  Otherwise TNode::UpdateMatrix should be called before.
   virtual void        Local2Master(const Double_t *local, Double_t *master);

/// Convert one point from local system to master reference system.
///  Note that before invoking this function, the global rotation matrix
///  and translation vector for this node must have been computed.
///  This is automatically done by the Paint functions.
///  Otherwise TNode::UpdateMatrix should be called before.
   virtual void        Local2Master(const Float_t *local, Float_t *master);

/// List Referenced object with current parameters.  1 2 3 4 5 x
   virtual void        ls(Option_t *option="2") const; // *MENU*

/// Convert one point from master system to local reference system.
///  Note that before invoking this function, the global rotation matrix
///  and translation vector for this node must have been computed.
///  This is automatically done by the Paint functions.
///  Otherwise TNode::UpdateMatrix should be called before.
   virtual void        Master2Local(const Double_t *master, Double_t *local);

/// Convert one point from master system to local reference system.
///  Note that before invoking this function, the global rotation matrix
///  and translation vector for this node must have been computed.
///  This is automatically done by the Paint functions.
///  Otherwise TNode::UpdateMatrix should be called before.
   virtual void        Master2Local(const Float_t *master, Float_t *local);

/// Paint Referenced node with current parameters.
///  - vis = 1  (default) shape is drawn
///  - vis = 0  shape is not drawn but its sons may be not drawn
///  - vis = -1 shape is not drawn. Its sons are not drawn
///  - vis = -2 shape is drawn. Its sons are not drawn
   virtual void        Paint(Option_t *option="");
   virtual void        RecursiveRemove(TObject *obj);/// Recursively remove object from the list of nodes of this node.
   virtual void        SetMatrix(TRotMatrix *matrix=0) {fMatrix = matrix;}
   virtual void        SetName(const char *name);/// Change the name of this Node

/// Set the pointer to the parent, keep parents informed about who they have
   virtual void        SetParent(TNode *parent);

/// Change the name and title of this Node
   virtual void        SetNameTitle(const char *name, const char *title);
   virtual void        SetPosition( Double_t x=0, Double_t y=0, Double_t z=0) {fX=x; fY=y; fZ=z;}

/// Set visibility for this node and its sons.
///  - vis = 3  node is drawn and its sons are drawn
///  - vis = 2  node is not drawn but its sons are drawn
///  - vis = 1  (default) node is drawn
///  - vis = 0  node is not drawn
///  - vis = -1 node is not drawn. Its sons are not drawn
///  - vis = -2 node is drawn. Its sons are not drawn
///  - vis = -3 Only node leaves are drawn
///  - vis = -4 Node is not drawn. Its immediate sons are drawn
   virtual void        SetVisibility(Int_t vis=1); // *MENU*

/// Return total size of this 3-D Node with its attributes.
   virtual void        Sizeof3D() const;

/// Update global rotation matrix/translation vector for this node
/// this function must be called before invoking Local2Master
   virtual void        UpdateMatrix();

/// Compute new translation vector and global matrix.
///  - dx      old translation vector
///  - rmat    old global matrix
///  - x,y,z   offset of new local system with respect to mother
///  - dxnew   new translation vector
///  - rmatnew new global rotation matrix
   virtual void        UpdateTempMatrix(const Double_t *dx1,const Double_t *rmat1,
                              Double_t x, Double_t y, Double_t z, Double_t *matrix,
                              Double_t *dxnew, Double_t *rmatnew);
```



<!-- TNode.md ends here -->
