#include "qwotreeview.h"
#include <QMouseEvent>
#include <QtDebug>

QWoTreeView::QWoTreeView(QWidget *parent)
    :QTreeView (parent)
{

}

void QWoTreeView::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Up || e->key() == Qt::Key_Down) {
        clearSelection();
        QTreeView::keyPressEvent(e);
        QItemSelectionModel *model = selectionModel();
        QModelIndex idx = currentIndex();
        if(idx.isValid()){            
            model->select(currentIndex(), QItemSelectionModel::SelectCurrent|QItemSelectionModel::Rows);
        }
    }else if(e->key() == Qt::Key_Return) {
        emit returnKeyPressed();
    }else{
        QTreeView::keyPressEvent(e);
    }
}

void QWoTreeView::mousePressEvent(QMouseEvent *e)
{
    QTreeView::mousePressEvent(e);
    QItemSelectionModel *model = selectionModel();
    if(e->button() == Qt::LeftButton){
        clearSelection();
        QModelIndex idx = indexAt(e->pos());
        if(idx.isValid()){
            setCurrentIndex(idx);
            model->select(idx, QItemSelectionModel::Select);
        }else{
            setCurrentIndex(QModelIndex());
        }
    }else{
        QModelIndex idx = indexAt(e->pos());
        if(!idx.isValid()) {
            clearSelection();
            setCurrentIndex(QModelIndex());
            return;
        }
        QModelIndexList idxs = selectedIndexes();
        for(int i  = 0; i < idxs.length(); i++) {
            if(idx == idxs.at(i)) {
                return;
            }
        }
        clearSelection();
        setCurrentIndex(idx);
        model->select(idx, QItemSelectionModel::Select);
    }
}

void QWoTreeView::mouseReleaseEvent(QMouseEvent *e)
{
    QTreeView::mouseReleaseEvent(e);
}

void QWoTreeView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QTreeView::currentChanged(current, previous);
    emit itemChanged(current);
}
