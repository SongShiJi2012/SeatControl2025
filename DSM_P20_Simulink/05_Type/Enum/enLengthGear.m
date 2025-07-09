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
            desc = 'enNULL��������λ����&#10;enLengthGear_0������0����&#10;enLengthGear_1������1����&#10;enLengthGear_2������2����&#10;enLengthGear_3������3����&#10;enLengthGear_4������4����&#10;enLengthGear_5������5����&#10;enLengthGear_6������6����,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
