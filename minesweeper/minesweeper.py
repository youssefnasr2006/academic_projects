from tkinter import *# tkinter module from python library
from tkinter import messagebox
import random

def mine_grid(rows, columns, mines_number):# make the grid of the game
    grid = []
    mines = set()
    for m in range(rows):
        row_buttons = []
        for n in range(columns):
            button = Button(center_frame, text="   ", height=int(2.5), width=5)
            button.grid(row=m, column=n, padx=1)
            button.bind("<Button-1>", lambda event, r=m, c=n: reveal_square(r, c))
            button.bind("<Button-3>", lambda event, r=m, c=n: add_flag(r, c))
            row_buttons.append(button)
        grid.append(row_buttons)

    while mines_number > len(mines):# add mines to cells randomly and store in mines
        mine = (random.randint(0, rows-1), random.randint(0, columns-1))
        if mine not in mines:
            mines.add(mine)

    return grid, mines

def reveal_square(row, col):# it take cells coordinate and see if it have mine or not to take certain actions
    global mines_number, revealed_squares_count
    if (row, col) in mines:
        reveal_mine(row, col)
    else:
        count = count_adjacent_mines(row, col)
        grid[row][col].config(text=str(count), bg="lightgray", state=DISABLED)
        revealed_squares_count += 1
        check_win()

def add_flag(row, col):# to add flag to the cell
    button = grid[row][col]
    if button['text'] == "Flag":
        button.config(text="  ")
    elif button["state"] == NORMAL:
        button.config(text="Flag", bg="blue", fg="white")
        check_win()

def reveal_mine(row, column):# it configure mine cell when it reveals and shows game over message
    global mines_number, revealed_mines
    for mine_row, mine_column in mines:
        grid[mine_row][mine_column].config(bg="red", text="mine", state=DISABLED)
    revealed_mines.update(mines)
    update_mines_left_label()
    messagebox.showinfo("Minesweeper game", message="Game over")

def count_adjacent_mines(row, col):# it count the number of mines that surrounds the empty revealed cell
    count = 0
    for i in range(row - 1, row + 2):
        for j in range(col - 1, col + 2):
            if (i, j) in mines:
                count += 1
    return count

def check_win():# it congrats the user when he reveal all empty cell
    global revealed_squares_count
    if revealed_squares_count == (len(grid) * len(grid[0])) - len(mines):
        messagebox.showinfo("Minesweeper", " CONGRATULATIONS, YOU WIN!!!!!")
        mine.quit()

def update_mines_left_label():# it calculates the number of mines left
    mines_left_label.config(text=f"Mines Left: {mines_number - len(revealed_mines)}")

mine = Tk()
mine.geometry('845x510')
mine.title('Minesweeper Game')
mine.resizable(False, False)
mine.configure(bg="grey")

top_frame = Frame(mine, bg='black', height=20, width=600)
top_frame.place(x=130, y=0)

side_frame = Frame(mine, bg='black', width=130, height=900)  # score frame
side_frame.place(x=0, y=0)

center_frame = Frame(mine, bg='blue', width=470, height=410)
center_frame.place(x=130, y=96)

mines_number = 30
revealed_mines = set()
revealed_squares_count = 0

grid, mines = mine_grid(10, 15, mines_number)

mines_left_label = Label(top_frame, text=f"Mines Left: {mines_number}", fg="white", bg="black")
mines_left_label.pack()

mine.mainloop()