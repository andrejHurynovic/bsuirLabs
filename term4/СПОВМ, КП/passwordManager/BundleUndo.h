#ifndef BUNDLEUNDO_H
#define BUNDLEUNDO_H

enum UndoOperation  {
    create,
    remove,
    edit,
};

class BundleUndo {
    
    enum UndoOperation type;
    
public:
    BundleUndo();
    void undo();
    void redo();
};

#endif // BUNDLEUNDO_H
