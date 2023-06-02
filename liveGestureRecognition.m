function liveGestureRecognition(trainedClassifier)

%% Initialize variables
ports = serialportlist;  
freeports = serialportlist("available");
s = serialport("COM4",9600);
a = arduino('COM6', 'Uno');
size = [100 2];
varTypes = {'double', 'string'};
varNames = {'RawCode','Gesture'};
A = table('Size', size,'VariableTypes',varTypes,'VariableNames',varNames);
    for i = 1:1:100

       while i > 1

        A.RawCode(i) = str2double(readline(s)); 
        yfit = trainedClassifier.predictFcn(A(i,["RawCode","Gesture"]))

       if yfit == "No gesture"
       writePWMDutyCycle(a, 'D5', 0);
       writePWMDutyCycle(a, 'D9', 0);

       elseif yfit == "Gesture 2"
       writeDigitalPin(a, 'D4', 1);
       writeDigitalPin(a, 'D2', 1);
       writePWMDutyCycle(a, 'D5', 0.4);
       writePWMDutyCycle(a,'D9', 0.4);
     
       elseif yfit == "Gesture 4"
       writeDigitalPin(a, 'D4', 0);
       writePWMDutyCycle(a, 'D5', 0.4);
       writeDigitalPin(a, 'D2', 0);             
       writePWMDutyCycle(a,'D9', 0.4);

       elseif yfit == "Gesture 1"
        writeDigitalPin(a, 'D4', 1);
       writeDigitalPin(a, 'D2', 0);
       writePWMDutyCycle(a, 'D5', 0.6);
       writePWMDutyCycle(a,'D9', 0.6);

       elseif yfit == "Gesture 3"
        writeDigitalPin(a, 'D4', 0);
       writeDigitalPin(a, 'D2', 1);
       writePWMDutyCycle(a, 'D5', 0.6);
       writePWMDutyCycle(a,'D9', 0.6);
       
       
       end
       
%         x = motorControls(string(yfit));
%         plot(A.RawCode(i:end))
%         ylim([1.3e7 1.83e7])
%         gesture = cellstr(yfit) 
%         text(i, 1.76e7, gesture, 'FontSize', 24, 'Color', 'red')
%         
%         drawnow
        end
    end
%% Step 1: Run live gesture recognition
% tic
%   
%     for i = 1:1:100
%         tabular: insert data into the ith row and 1st variable in the table
%         A(i,1) = str2double(readline(s));
%         A(isnan(A)) = [];   
%         while i > 1
%         Step 2: Predict gesture using extracted data
%        yfit = trainedClassifier.predictFcn(A)
%         plot(A(2:end))
%         ylim([1.849e7 1.87e7])
%         text(gesturePred,'FontSize', 18, 'Color', 'green')
%         
%         drawnow
%    
%         end 
    
% 
% toc 


    %end

