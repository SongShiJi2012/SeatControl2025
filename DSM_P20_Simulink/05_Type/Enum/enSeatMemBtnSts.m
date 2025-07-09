%% Create enSeatMemBtnSts enum

classdef enSeatMemBtnSts < Simulink.IntEnumType

    enumeration
        EN_SEAT_BTN_INACTIVE(0)
        EN_SEAT_BTN_CALL_MEM_POSI(1)
        EN_SEAT_BTN_MEM_CURR_POSI(2)
        EN_SEAT_BTN_CLE_MEM_POSI(3)
        EN_SEAT_BTN_INVALID(7)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enSeatMemBtnSts.EN_SEAT_BTN_INACTIVE;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '×ùÒÎ¼ÇÒä°´¼üÇëÇó×´Ì¬:&#10;0x0: Inactive&#10;0x1: Call Memory Position&#10;0x2: Memorize Current Position&#10;0x3: Clean Up Memory Position&#10;0x4~0x6: Reserved&#10;0x7: Invalid,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
