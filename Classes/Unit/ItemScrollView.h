
#ifndef __ItemScrollView__
#define __ItemScrollView__


#include "cocos2d.h"
#include "Heads.h"

USING_NS_CC;

class ItemCell:public Node {
    
    
public:
    static ItemCell* create(const std::string bgPath,const std::string bgHighlight,const std::string btn,const std::string lock);
    bool init(const std::string bgPath,const std::string bgHighlight,const std::string btn,const std::string lock);
    
    void setSelected(bool selected);
    
    std::function<void(ItemCell*)> onItemCellSelected;
private:
    Sprite* m_pBg;
    Sprite* m_pBgHeighlight;
    Button* m_pBtn;
    Sprite* m_pLock;
    std::string m_sBgPath;
    std::string m_sBgHighlightPath;
};

class ItemScrollView : public Layer,public TableViewDataSource,public TableViewDelegate

{
public:
    ItemScrollView();
    ~ItemScrollView();
    
    static ItemScrollView* createWithSize(Size size);
    virtual bool init(Size size);
    
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx) {
        return cellSizeForTable(table);
    };
    virtual Size cellSizeForTable(TableView *table) {
        return Size(640,140);
    };
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    
    std::function<void(int index,DecorateConfigData Data)> onItemCellSelected;
    
    void reloadData()
    {
        m_pCurCell = nullptr;
        m_pTableView->reloadData();
    }
    
    void scrollToNext();
    
    void scrollToPre();
    
    int levelFreeCount;
    int lockFreeCount;

    std::string bgPath;
    std::string bgHighlightPath;
    std::string btnPathEX;
    DecorateConfigData decorationData;
    
    int indexOffset; //偏移量（有的可能从0开始有的可能从1开始）
    
    TableViewCell* m_pCurCell;
protected:
    void _itemSelected(ItemCell*);
protected:
    int colNum;
    TableView* m_pTableView;
};

#endif