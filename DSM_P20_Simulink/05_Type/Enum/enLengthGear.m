%% Create enLengthGear enum

classdef enLengthGear < Simulink.IntEnumType

    enumeration
        enNULL(0)
        enLengthGear_0(1)
        enLengthGear_1(2)
        enLengthGear_2(3)
        enLengthGear_3(4)
        enLengthGear_4(5)
        enLengthGear_5(6)
        enLengthGear_6(7)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enLengthGear.enNULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'enNULL£¨ÎÞ×ÝÏòµµÎ»ÇëÇó£©&#10;enLengthGear_0£¨×ÝÏò0µµ£©&#10;enLengthGear_1£¨×ÝÏò1µµ£©&#10;enLengthGear_2£¨×ÝÏò2µµ£©&#10;enLengthGear_3£¨×ÝÏò3µµ£©&#10;enLengthGear_4£¨×ÝÏò4µµ£©&#10;enLengthGear_5£¨×ÝÏò5µµ£©&#10;enLengthGear_6£¨×ÝÏò6µµ£©,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
