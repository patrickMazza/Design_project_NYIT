ports = serialportlist;
freeports = serialportlist("available");
 s =serialport("COM4",9600);
%A = zeros(10,10);

tic
for i = 1:1:100
    A(i) = str2double(readline(s))
    A(isnan(A)) = []; 
    plot(A(1:end))
    ylim([1.3e7 1.83e7])
    drawnow
end

%  for i = 1:1:10
%      for j = 1:1:10
%         A(i,j) =  str2double(readline(s));
%         plot(A)
%      end
%  end 
toc
save('A.mat','A');


