%% Create enBackGear enum

classdef enBackGear < Simulink.IntEnumType

    enumeration
        enNULL(0)
        enBackGear_0(1)
        enBackGear_1(2)
        enBackGear_2(3)
        enBackGear_3(4)
        enBackGear_4(5)
        enBackGear_5(6)
        enBackGear_6(7)
        enBackGear_7(8)
        enBackGear_8(9)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enBackGear.enNULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'enNULL£¨ÎÞ¿¿±³µµÎ»ÇëÇó£©&#10;enBackGear_0£¨¿¿±³0µµ£©&#10;enBackGear_1£¨¿¿±³1µµ£©&#10;enBackGear_2£¨¿¿±³2µµ£©&#10;enBackGear_3£¨¿¿±³3µµ£©&#10;enBackGear_4£¨¿¿±³4µµ£©&#10;enBackGear_5£¨¿¿±³5µµ£©&#10;enBackGear_6£¨¿¿±³6µµ£©&#10;enBackGear_7£¨¿¿±³7µµ£©&#10;enBackGear_8£¨¿¿±³8µµ£©,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
