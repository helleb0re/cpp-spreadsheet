#include "sheet.h"

#include "cell.h"
#include "common.h"

#include <iostream>
#include <cassert>

using namespace std::literals;

void Sheet::SetCell(Position pos, std::string text) {
    PositionIsValid(pos);

    if (printable_size_.rows < pos.row + 1) {
        printable_size_.rows = pos.row + 1;
    }

    if (printable_size_.cols < pos.col + 1) {
        printable_size_.cols = pos.col + 1;
    }

    if (sheet_.count(pos) == 0) {
        sheet_[pos] = std::make_unique<Cell>(*this);
    }
    sheet_[pos]->Set(text);
}

const CellInterface *Sheet::GetCell(Position pos) const {
    PositionIsValid(pos);

    if (sheet_.count(pos) == 0) {
        return nullptr;
    }

    return sheet_.at(pos).get();
}

CellInterface *Sheet::GetCell(Position pos) {
    PositionIsValid(pos);

    if (sheet_.count(pos) == 0) {
        return nullptr;
    }

    return sheet_.at(pos).get();
}

void Sheet::ClearCell(Position pos) {
    PositionIsValid(pos);

    if (!GetCell(pos)) return;

    sheet_.erase(pos);

    if (printable_size_.rows == pos.row + 1 ||
        printable_size_.cols == pos.col + 1) {
        RecalculatePrintableSize();
    }
}

Size Sheet::GetPrintableSize() const {
    return printable_size_;
}

void Sheet::PrintValues(std::ostream &output) const {
    for (int i = 0; i < printable_size_.rows; ++i) {
        for (int j = 0; j < printable_size_.cols; ++j) {
            auto cell = GetCell({i, j});
            Cell::Value ans;
            if (cell) {
                ans = cell->GetValue();
            }
            switch (ans.index()) {
                case 0: {
                    output << std::get<0>(ans) << (j + 1 == printable_size_.cols ? "" : "\t");
                    break;
                }
                case 1: {
                    output << std::get<1>(ans) << (j + 1 == printable_size_.cols ? "" : "\t");
                    break;
                }
                case 2: {
                    output << std::get<2>(ans) << (j + 1 == printable_size_.cols ? "" : "\t");
                    break;
                }
                default:
                    assert(false);
            }
        }
        output << '\n';
    }
}

void Sheet::PrintTexts(std::ostream &output) const {
    for (int i = 0; i < printable_size_.rows; ++i) {
        for (int j = 0; j < printable_size_.cols; ++j) {
            auto cell = GetCell({i, j});
            std::string ans;
            if (cell) {
                ans = cell->GetText();
            }
            output << ans << (j + 1 == printable_size_.cols ? "" : "\t");
        }
        output << '\n';
    }
}

void Sheet::PositionIsValid(Position pos) {
    if (!pos.IsValid()) {
        throw InvalidPositionException("Pos is invalid"s);
    }
}

void Sheet::RecalculatePrintableSize() {
    Size new_size{-1, -1};
    for (const auto &[pos, cell]: sheet_) {
        if (new_size.rows < pos.row) {
            new_size.rows = pos.row;
        }
        if (new_size.cols < pos.col) {
            new_size.cols = pos.col;
        }
    }
    printable_size_ = {new_size.rows + 1, new_size.cols + 1};
}


std::unique_ptr<SheetInterface> CreateSheet() {
    return std::make_unique<Sheet>();
}