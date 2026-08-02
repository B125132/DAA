set title 'Fair Coin vs Biased Coin'
set xlabel 'Number of Tosses'
set ylabel 'Probability of HEAD'
set yrange [0:1]
set grid
plot 'coin_data.txt' using 1:2 with lines title 'Fair Coin (p=0.5)', 'coin_data.txt' using 1:3 with lines title 'Biased Coin (p=0.7)'
pause -1 'Press Enter to close graph'
